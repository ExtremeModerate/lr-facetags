// Copyright 2014, University of Freiburg, Machine Learning Lab
// Authors: Daniel Leinfelder, Manuel Bühler, Christina Hernández Wunsch, Tobias Strickfaden


#include "FacetagsUI.h"
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
#include "./FacetagsDetection.h"
#include "./readWriteObjectFile.h"
#include "./FaceObject.h"

using namespace std;


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->pushDetect, SIGNAL(clicked()), this, SLOT(detect()));
  connect(ui->pushOpenFolder, SIGNAL(clicked()), this, SLOT(openFolder()));
  connect(ui->pushSaveLog, SIGNAL(clicked()), this, SLOT(saveLog()));
  connect(ui->pushLoadAllRuns, SIGNAL(clicked()), this, SLOT(loadAllRuns()));
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::detect() {
  string sClassifier = ui->dropDownDetect->currentText().toUtf8().data();
  string sPath = ui->inputPath->text().toUtf8().constData();
  string sFileName, sFullPath, sDate;

  vector<FaceObject> faceObjects;

  QDateTime dateTime;
  QString date = dateTime.currentDateTime().toString();
  sDate = dateTime.currentDateTime().toString().toUtf8().constData();
  QString path = ui->inputPath->text();
  QDir dir = path;
  QString fullPath = dir.absolutePath();


  // create subfolders
  if (!QDir(path + "/metaface").exists()) {
    QDir().mkdir("metaface");
  }
  QDir dirr = QDir::root(); 
  dirr.mkpath(fullPath + "/metaface/" + date +"/");

  // iterate through Image folder
  dir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDot | QDir::NoDotDot);
  // add QDirIterator::Subdirectories as argument if you want to iterate trough subfolders
  QDirIterator it(dir);
  while(it.hasNext()) {
    it.next();
    sFullPath = it.filePath().toUtf8().constData();
    sFileName = it.fileName().toUtf8().constData();
    faceObjects = detectFaces(sFullPath, sClassifier);
    writeObjectFile(faceObjects, sPath + "/metaface/" + sDate + "/" + sFileName + ".txt");
    
  }
  ui->outputText->append("Detection done!");
  ui->outputRuns->append(date);
}

void MainWindow::openFolder() {
  QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                             "/home",
                                             QFileDialog::ShowDirsOnly
                                             | QFileDialog::DontResolveSymlinks);
  ui->inputPath->setText(dir);
}

void MainWindow::saveLog() {
  // TODO
  QFile file ("log.txt");
  if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
  QTextStream out(&file);
  out << ui->outputText->document()->toHtml();
  file.close(); 
  }
}

void MainWindow::loadAllRuns() {
  QString path = ui->inputPath->text() + "/metaface/";
  cout << path.toUtf8().constData() << endl;

  QStringList all_dirs;
  all_dirs << path;
  QDirIterator directories(path, QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
  while(directories.hasNext()) {
    directories.next();
    QString bla = directories.filePath();
    cout << bla.toUtf8().constData() << endl;
    all_dirs << directories.filePath();
 }
  
}
