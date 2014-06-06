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


using namespace std;

std::string sDate;
std::string sFullPath;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->pushDetect, SIGNAL(clicked()), this, SLOT(detect()));
  connect(ui->pushOpenFolder, SIGNAL(clicked()), this, SLOT(openFolder()));
  connect(ui->pushSaveLog, SIGNAL(clicked()), this, SLOT(saveLog()));
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::detect() {
  string sClassifier = ui->dropDownDetect->currentText().toUtf8().data();
  QString path = ui->inputPath->text();

  string sFileName;
  QDateTime dateTime;
  QString date = dateTime.currentDateTime().toString();
  sDate = date.toUtf8().constData();
  ////////////cout << sDate << endl;

  QDir dir = path;
  QString fullPath = dir.absolutePath();
  sFullPath = path.toUtf8().constData();

  // create subfolders
  if (!QDir(path + "/metaface").exists()) {
    QDir().mkdir("metaface");
  }
  QDir dirr = QDir::root(); 
  dirr.mkpath(fullPath + "/metaface/" + date +"/");

  // iterate through folder
  dir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDot | QDir::NoDotDot);
  // add QDirIterator::Subdirectories as argument if you want to iterate trough subfolders
  QDirIterator it(dir);
  while(it.hasNext()) {
    it.next();
    sFileName = it.fileName().toUtf8().constData();
    detectFaces(sFullPath, sFileName, sClassifier);
  }
  ui->outputText->append("Detection done!");
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
