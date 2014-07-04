// Copyright 2014, University of Freiburg, Machine Learning Lab
// Authors: Daniel Leinfelder, Manuel Bühler, Christina Hernández Wunsch, Tobias Strickfaden

#ifndef MAINUI_H
#define MAINUI_H

#include <QMainWindow>

extern QStringList benchmarkTargets;
extern std::string sDate;

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui;

private slots:
  void detect();
  void recognize();
  void openFolder();
  void saveLog();
  void clearLog();
  void clearRuns();
  void loadAllRuns();
  void loadRun();
  void compareDetection();
  void compareRecognition();
};

#endif // MAINUI_H
