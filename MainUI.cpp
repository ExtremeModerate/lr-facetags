// Copyright 2014, University of Freiburg, Machine Learning Lab
// Authors: Daniel Leinfelder, Manuel Bühler, Christina Hernández Wunsch, Tobias Strickfaden


#include "MainUI.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFileDialog>
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QTextStream>
#include <QTextBrowser>
#include <QDateTime>
#include <QEventLoop>
#include <iostream>
#include "./Detection.h"
#include "./RecognitionOpenCV.h"
#include "./readWriteObjectFile.h"
#include "./FaceObject.h"
#include "benchmark.h"
#include "plotdialog.h"

using namespace std;
using namespace cv;

QStringList benchmarkTargets; // list of targets for benchmarking
string sTimestamp; // timestamp with chosen method of the last detection/recognition run
struct PlotStruct
{
    QVector<double> pr, rc;
    QString name;
};
vector<PlotStruct> vPlots;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->pushDetect, SIGNAL(clicked()), this, SLOT(detect()));
  connect(ui->pushRecognize, SIGNAL(clicked()), this, SLOT(recognize()));
  connect(ui->pushOpenFolder, SIGNAL(clicked()), this, SLOT(openFolder()));
  connect(ui->pushSaveLog, SIGNAL(clicked()), this, SLOT(saveLog()));
  connect(ui->pushClearA, SIGNAL(clicked()), this, SLOT(clearLog()));
  connect(ui->pushClearB, SIGNAL(clicked()), this, SLOT(clearRuns()));
  connect(ui->pushLoadAllRuns, SIGNAL(clicked()), this, SLOT(loadAllRuns()));
  connect(ui->pushLoadRun, SIGNAL(clicked()), this, SLOT(loadRun()));
  connect(ui->pushCompareDetection, SIGNAL(clicked()), this, SLOT(compareDetection()));
  connect(ui->pushCompareRecognition, SIGNAL(clicked()), this, SLOT(compareRecognition()));
  connect(ui->pushShowPlot, SIGNAL(clicked()), this, SLOT(showPlot()));
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::detect() {
  string sFileName, sFullPath;
  vector<FaceObject> faceObjects;

  // parse arguments
  string sClassifier = ui->dropDownDetect->currentText().toUtf8().data();
  string sPath = ui->inputPath->text().toUtf8().constData();

  // create subfolder with a timestamp and chosen classifiern
  QString path = ui->inputPath->text();
  QDir dir = path;
  QString fullPath = dir.absolutePath();
  if (!QDir(path + "/metaface").exists()) {
    QDir().mkdir("metaface");
  }
  QDateTime dateTime;
  QString date = dateTime.currentDateTime().toString();
  sTimestamp = dateTime.currentDateTime().toString().toUtf8().constData();
  sTimestamp = sTimestamp + "_" + sClassifier;
  QDir dirr = QDir::root();
  QString timestamp = QString::fromStdString(sTimestamp);
  dirr.mkpath(fullPath + "/metaface/" + timestamp +"/");

  // iterate through image folder and run detection on each image
  dir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDot | QDir::NoDotDot | QDir::NoSymLinks);
  // add QDirIterator::Subdirectories as argument if you want to iterate trough subfolders
  QDirIterator it(dir);
  while(it.hasNext()) {
    it.next();
    sFileName = it.fileName().toUtf8().constData();
    faceObjects = detectFaces(sPath, sFileName, sClassifier);
    writeObjectFile(faceObjects, sPath + "/metaface/" + sTimestamp + "/"  + sFileName + ".txt");
    
  }

  ui->outputText->append("Detection done!");
}

void MainWindow::recognize() {
  // check if detection has been run
  if (sTimestamp.empty()) {
    ui->outputText->append("Need to run Detection first!");
    return;
  }

  // parse arguments
  string sClassifier = ui->dropDownRecognize->currentText().toUtf8().data();
  string sPath = ui->inputPath->text().toUtf8().constData();
  string sFullPath = sPath + "/metaface/" + sTimestamp;
  int sizeTrainingSet = ui->spinBoxTrainingSet->value();

  // iterate through the previous detected Faces
  std::vector<std::vector<FaceObject> > faceObjects;
  QString path = sFullPath.c_str();
  QDir dir = path;
  dir.setFilter(QDir::Files | QDir::NoDot | QDir::NoDotDot | QDir::NoSymLinks);
  QDirIterator it(dir);
  while(it.hasNext()) {
    it.next();
    vector<FaceObject> objects = readObjectFile(it.filePath().toUtf8().constData());
    faceObjects.push_back(objects);   
  }

  // edit faces for usage and save them to the faceObjects
  int counter = 0;
  Size size(100,100);
  vector<Mat> trainingImages;
  vector<int> trainingLabels;
  for (size_t i = 0; i < faceObjects.size(); i++) {
    for (size_t j = 0; j < faceObjects[i].size(); j++) {
      string file = sPath + "/" + faceObjects[i][j].fileName;
      Mat image = imread(file);
      if (!image.empty()) {
        // crop the face
        Rect crop(faceObjects[i][j].x, faceObjects[i][j].y, faceObjects[i][j].width, faceObjects[i][j].height);
        image = image(crop);

        // convert to grayscale
        cvtColor(image, image, COLOR_BGR2GRAY);
        equalizeHist(image, image);
         
        // resize to 100x100
        cv::resize(image, image, size);

        faceObjects[i][j].image = image;

        // open dialog to tag the training set
        if (counter < sizeTrainingSet) {
          TagTrainingSetDialog tagDialog;
          tagDialog.setImage(image);
          tagDialog.exec();
          int tag = tagDialog.getTag();
          faceObjects[i][j].objectID = tag;
          trainingImages.push_back(image);
          trainingLabels.push_back(tag);
          counter++;

        }
      }
    }
  }

  // start the chosen recognition method
  if (sClassifier == "Eigenfaces OpenCV") {
    recognizeEigenfacesOpenCV(faceObjects, trainingImages, trainingLabels);
  } 
  else if (sClassifier == "Fisherfaces OpenCV") {
    recognizeFisherfacesOpenCV(faceObjects, trainingImages, trainingLabels);
  }
  else if (sClassifier == "LBP Histograms OpenCV") {
    recognizeLBPHistogramsOpenCV(faceObjects, trainingImages, trainingLabels);
  }

  // get a new timestamp, create a subfolder in metaface/ and save the results
  path = ui->inputPath->text();
  dir = path;
  QDateTime dateTime;
  QString date = dateTime.currentDateTime().toString();
  QDir dirr = QDir::root();
  sTimestamp = dateTime.currentDateTime().toString().toUtf8().constData();
  sTimestamp = sTimestamp + "_" + sClassifier;
  QString timestamp = QString::fromStdString(sTimestamp);
  path = dir.absolutePath() + "/metaface/" + timestamp;
  cout << path.toUtf8().constData() << endl;
  dirr.mkpath(path);

  writeObjectFileVector(faceObjects, path.toUtf8().constData());

  ui->outputText->append("Recognition Done!");
}

void MainWindow::openFolder() {
    QString currentDir = ui->inputPath->text();
    if(!QDir(currentDir).exists()) currentDir = "/home";
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                             currentDir,
                                             QFileDialog::ShowDirsOnly
                                             | QFileDialog::DontResolveSymlinks);
  ui->inputPath->setText(dir);
}

void MainWindow::saveLog() {
  QString name = QFileDialog::getSaveFileName(this, "Save file", "", ".txt");
  QFile file(name + ".txt");
  if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
  QTextStream out(&file);
  out << ui->outputText->toPlainText();
  file.close(); 
  }
}

void MainWindow::clearLog() {
  ui->outputText->clear();
}

void MainWindow::clearRuns() {
  benchmarkTargets.clear();
  ui->outputRuns->clear();
}

void MainWindow::loadAllRuns() {
  QString path = ui->inputPath->text() + "/metaface/";
  benchmarkTargets.clear();
  ui->outputRuns->clear();  
  QDirIterator directories(path, QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
  while(directories.hasNext()) {
    directories.next();
    QStringList tmp = directories.filePath().split("/");
    //benchmarkTargets << tmp.value(tmp.length()-1);
	  benchmarkTargets << directories.filePath();
    ui->outputRuns->append(tmp.value(tmp.length()-1));
  }
}

void MainWindow::loadRun() {
  QString currentDir = ui->inputPath->text();
  if(!QDir(currentDir).exists()) currentDir = "/home";
  QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                             currentDir,
                                             QFileDialog::ShowDirsOnly
                                             | QFileDialog::DontResolveSymlinks);
  QStringList tmp = dir.split("/");
  //benchmarkTargets << tmp.value(tmp.length()-1);
  benchmarkTargets << dir;
  ui->outputRuns->append(tmp.value(tmp.length()-1));
  benchmarkTargets.removeDuplicates();
}

void MainWindow::compareDetection() {
	ui->outputText->append("begin compareDetection()");
  QString gTruth = ui->inputPath->text() + "/.metaface";
  for (int i = 0; i < benchmarkTargets.size(); ++i) {
	QString work = benchmarkTargets.at(i);
    ui->outputText->append(work);
    //benchmarkResult bRes = benchmark(work.toAscii().data(), gTruth.toAscii().data(), 0.5, false);
    benchmarkResult bRes = benchmarkDetection(work.toAscii().data(), gTruth.toAscii().data(), 0.5);
    PlotStruct plot_struct;
    plot_struct.pr.push_back(bRes.precision);
    plot_struct.rc.push_back(bRes.recall);
    plot_struct.name = bRes.logFileName.c_str();
    vPlots.push_back(plot_struct);
    ui->outputText->append(bRes.toString().c_str());
  }
  ui->outputText->append("end compareDetection()");
}

void MainWindow::compareRecognition() {
  // TODO: Find bug in benchmarkRecognition ?
    ui->outputText->append("begin compareRecognition()");
  QString gTruth = ui->inputPath->text() + "/.metaface";
  for (int i = 0; i < benchmarkTargets.size(); ++i) {
    QString work = benchmarkTargets.at(i);
    ui->outputText->append(work);
    benchmarkResult bRes = benchmarkRecognition(work.toAscii().data(), gTruth.toAscii().data(), 0.5);
    ui->outputText->append(bRes.toString().c_str());
  }
  ui->outputText->append("end compareRecognition()");
}

void MainWindow::showPlot() {
    PlotDialog plotDialog(this);
    for(size_t i=0; i<vPlots.size(); i++)
    {
        plotDialog.addGraph(vPlots[i].pr, vPlots[i].rc, vPlots[i].name);
    }
    plotDialog.plotGraphs();
    plotDialog.exec();
}
