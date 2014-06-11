#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include <QString>
#include <QDebug>
#include <QListWidget>
#include "robwidget.h"
#include "mainwindow.h"
#include "dirent.h"
#include <sys/stat.h>
#include "tagelement.h"
#include "readWriteObjectFile.h"
#include "FaceObject.h"
#include <string>
#include <iostream>

class RobWidget;

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
     QListWidget *listObjects;
     QString selectedDirectory;
     QString selectedFile;

     void addObjectClicked(RobWidget *imageWidget, ObjectType objectType, QString objectID, double truncated, OcclusionLevel occluded, double scaleRation);
     void changeImage();
     void removeElements(QList<QListWidgetItem *> elements);

     QPixmap* frameAllFaces(QPixmap * pixmap, double scaleRatio);

     void saveFacesToDisk();

   protected:
     Manager() {}

   private:
     static Manager *instanz;
     bool directorySelected;
     //Ui::MainWindow *ui;

     std::vector<FaceObject> TagedElements;




};

#endif // MANAGER_H
