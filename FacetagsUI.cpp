// Copyright 2014, University of Freiburg, Machine Learning Lab
// Authors: Daniel Leinfelder, Manuel Bühler, Christina Hernández Wunsch, Tobias Strickfaden


#include "FacetagsUI.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFileDialog>
#include <QDir>
#include <QDirIterator>
#include "./FacetagsDetection.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->pushDetect, SIGNAL(clicked()), this, SLOT(detect()));
  connect(ui->pushOpenFolder, SIGNAL(clicked()), this, SLOT(openFolder()));
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::detect() {
  std::string classifier = ui->dropDownDetect->currentText().toAscii().data();
  QDir dir = ui->inputPath->text();
  
  // iterate through folder
  dir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDot | QDir::NoDotDot);
  QDirIterator it(dir, QDirIterator::Subdirectories);
  while(it.hasNext()) {
   std::string file = it.next().toUtf8().constData();
   detectFaces(file, classifier);
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
