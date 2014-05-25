#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include <QString>
#include <QDebug>
#include <QListWidget>
#include "mainwindow.h"
#include "dirent.h"
#include <sys/stat.h>

namespace Ui {
class MainWindow;
}

class Manager
{

public:
     static Manager* exemplar();
     void setSelectedDirectory(QString dir);
     void displayDirectory();
     //void setUi(Ui::MainWindow *ui);
     QListWidget *fileList;
     QString selectedDirectory;

   protected:
     Manager() {}

   private:
     static Manager *instanz;
     bool directorySelected;
     //Ui::MainWindow *ui;



};

#endif // MANAGER_H
