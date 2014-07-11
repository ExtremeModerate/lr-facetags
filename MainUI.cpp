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
#include <iostream>
#include "./Detection.h"
#include "./RecognitionOpenCV.h"
#include "./readWriteObjectFile.h"
#include "./FaceObject.h"

using namespace std;

QStringList benchmarkTargets;
string sDate;

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
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::detect() {
  string sClassifier = ui->dropDownDetect->currentText().toUtf8().data();
  string sPath = ui->inputPath->text().toUtf8().constData();
  string sFileName, sFullPath;

  vector<FaceObject> faceObjects;

  QDateTime dateTime;
  QString date = dateTime.currentDateTime().toString();
  sDate = dateTime.currentDateTime().toString().toUtf8().constData();
  QString path = ui->inputPath->text();
  QDir dir = path;
  QString fullPath = dir.absolutePath();


  // create subfolder
  if (!QDir(path + "/metaface").exists()) {
    QDir().mkdir("metaface");
  }
  QDir dirr = QDir::root(); 
  dirr.mkpath(fullPath + "/metaface/" + date +"/");

  // iterate through Image folder
  dir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDot | QDir::NoDotDot | QDir::NoSymLinks);
  // add QDirIterator::Subdirectories as argument if you want to iterate trough subfolders
  QDirIterator it(dir);
  while(it.hasNext()) {
    it.next();
    sFileName = it.fileName().toUtf8().constData();
    faceObjects = detectFaces(sPath, sFileName, sClassifier);
    writeObjectFile(faceObjects, sPath + "/metaface/" + sDate + "/" + sFileName + ".txt");
    
  }
  ui->outputText->append("Detection done!");
  ui->outputRuns->append(date);
  benchmarkTargets << date;
}

void MainWindow::recognize() {
  if (sDate.empty()) {
    ui->outputText->append("Need to run Detection first!");
    return;
  }
  string sClassifier = ui->dropDownRecognize->currentText().toUtf8().data();
  string sPath = ui->inputPath->text().toUtf8().constData();
  string sFullPath = sPath + "/metaface/" + sDate;
  QString path = sFullPath.c_str();
  QDir dir = path;
  std::vector<std::vector<FaceObject> > faceObjects;

  // iterate through the previous detected Faces
  dir.setFilter(QDir::Files | QDir::NoDot | QDir::NoDotDot | QDir::NoSymLinks);
  QDirIterator it(dir);
  while(it.hasNext()) {
    it.next();
    cout << "reading file:  " << it.filePath().toUtf8().constData() << endl;
    vector<FaceObject> objects = readObjectFile(it.filePath().toUtf8().constData());
    faceObjects.push_back(objects);
    
  }

  if (sClassifier == "Eigenfaces OpenCV" || 
      sClassifier == "Fisherfaces OpenCV" || 
      sClassifier == "LBP Histograms OpenCV") {
    recognizeOpenCV(faceObjects, sClassifier, sPath + "/");
  }
  writeObjectFileVector(faceObjects, sFullPath);
  ui->outputText->append("Recognition Done!");
}

void MainWindow::openFolder() {
  QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                             "/home",
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
    benchmarkTargets << tmp.value(tmp.length()-1);
    ui->outputRuns->append(tmp.value(tmp.length()-1));
  }
}

void MainWindow::loadRun() {
  QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                             "/home",
                                             QFileDialog::ShowDirsOnly
                                             | QFileDialog::DontResolveSymlinks);
  QStringList tmp = dir.split("/");
  benchmarkTargets << tmp.value(tmp.length()-1);
  ui->outputRuns->append(tmp.value(tmp.length()-1));
  benchmarkTargets.removeDuplicates();
}

void MainWindow::compareDetection() {
  // TODO 
  QString gTruth = ui->inputPath->text();
  for (int i = 0; i < benchmarkTargets.size(); ++i) {
    QString work = gTruth + "/" + benchmarkTargets.at(i);
  }
  ui->outputText->append("not implemented yet, need benchmark algorithm");
}

void MainWindow::compareRecognition() {
  // TODO 
  QString gTruth = ui->inputPath->text();
  for (int i = 0; i < benchmarkTargets.size(); ++i) {
    QString work = gTruth + "/" + benchmarkTargets.at(i);
    cout << work.toUtf8().constData() << endl;
  }
  ui->outputText->append("not implemented yet, need benchmark algorithm");
}
