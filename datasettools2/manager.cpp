#ifndef ROBWIDGET_H
#include "manager.h"
#endif // ROBWIDGET_H


Manager* Manager::instanz = 0;

Manager* Manager::exemplar()
{
  if( instanz == 0 ) {
    instanz = new Manager();
    instanz->selectedFace = -1;
  }

  instanz->directorySelected = false;
  return instanz;


  // setui list elements
}

Manager Manager() {
}


void Manager::setSelectedDirectory(QString dir) {
    qDebug()<<dir;
    this->directorySelected = true;
    this->selectedDirectory = dir;

    this->displayDirectory();
}

void Manager::displayDirectory() {
   //fileList->clear();
    fileList->clear();
    DIR *dir;
    struct dirent *ent;
    struct stat info;
    const char *c_str2 = this->selectedDirectory.toLocal8Bit().data();
    if ((dir = opendir (c_str2)) != NULL) {
      /* print all the files and directories within directory */
      while ((ent = readdir (dir)) != NULL) {
          stat(ent->d_name, &info);
          //if(!S_ISDIR (info.st_mode)) {
            //qDebug() << ent->d_name;
            new QListWidgetItem(ent->d_name, fileList);
          //}
      }
      closedir (dir);
    } else {
      /* could not open directory */
      perror ("");
      //return EXIT_FAILURE;
    }

}



////////////////////////////////////////////////// Options


// if the image changes we have to reset all markings and list elemets
void Manager::changeImage() {
    listObjects->clear();
    //ToDo: load all stored objects from the disk
    std::string file = selectedDirectory.toStdString() + "/.metaface/" + selectedFile.toStdString() + ".txt";
    this->TagedElements = readObjectFile(file);

    for(std::vector<FaceObject>::iterator it = this->TagedElements.begin(); it != this->TagedElements.end(); ++it) {
        FaceObject fo = *it;
        std::cerr << fo.objectID;
        new QListWidgetItem(QString::fromStdString(fo.objectID), listObjects);
    }

    qDebug() << "loaded" << TagedElements.size() << "elements";
}



void Manager::addObjectClicked(RobWidget *imageWidget, ObjectType objectType, QString objectID, double truncated, OcclusionLevel occluded, double scaleRation) {
    qDebug() << "add Object Clicked!";
    QRect x = imageWidget->getBandBox();

    qDebug() << x;

    FaceObject * t = new FaceObject();
    t->x = (int) (x.x());
    t->y = (int) (x.y());
    t->height = (int) (x.height());
    t->width = (int) (x.width());
    t->truncationLevel = (float) truncated;
    t->occlusionLevel = occluded;
    t->objectID = objectID.toStdString();
    t->objectType = objectType;
    this->TagedElements.push_back(*t);

    // add element to the list in the ui
    new QListWidgetItem(objectID, listObjects);

    this->saveFacesToDisk();

}

void Manager::saveFacesToDisk() {
    // save vector to disk
    std::string file = selectedDirectory.toStdString() + "/.metaface/" + selectedFile.toStdString() + ".txt";
    QDir dir(selectedDirectory + "/.metaface/");
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    bool res = writeObjectFile(this->TagedElements, file, false);

    if(!res) {
        qDebug() << "!!!!!faild to save to file!!!!!!";
        //ToDo: Maybe handle a save error
    } else {
        std::cerr << "saved to file: " << file << " \n" << endl;
    }
}


void Manager::removeElements(QList<QListWidgetItem *> elements) {
    for(QList<QListWidgetItem *>::iterator it = elements.begin(); it != elements.end(); ++it) {
        QListWidgetItem item = **it;
        qDebug() << item.text();
        /*for(std::vector<FaceObject>::iterator it2 = this->TagedElements.begin(); it2 != this->TagedElements.end(); ++it2) {
            FaceObject fo = *it2;
            if(fo.objectID == item.text().toStdString()) {
                qDebug() << "found the item!";
                this->TagedElements.erase(it2);

            }
        }*/
        for (std::vector<FaceObject>::iterator it2 = this->TagedElements.begin(); it2 != this->TagedElements.end();) {
            FaceObject fo = *it2;
            if (fo.objectID == item.text().toStdString()) {
              it2 = this->TagedElements.erase(it2);
            } else {
              ++it2;
            }
        }

    }
}



////////////////////////////////////////////////////////////

// add a border to all stored faces
QPixmap * Manager::frameAllFaces(QPixmap * pixmap, double scaleRatio) {
    QPainter qPainter(pixmap);
    qPainter.setBrush(Qt::NoBrush);
    qPainter.setPen(Qt::red);

    int element = 0;

    for(std::vector<FaceObject>::iterator it = this->TagedElements.begin(); it != this->TagedElements.end(); ++it) {
        FaceObject fo = *it;
        if(element != selectedFace) {
            qPainter.setPen(Qt::red);
        } else {
            qPainter.setPen(Qt::green);
        }
        qPainter.drawRect((int)(fo.x * scaleRatio),(int)(fo.y * scaleRatio),(int)(fo.width * scaleRatio),(int) (fo.height * scaleRatio));
        element++;
    }

    return pixmap;
}


void Manager::handleKeyEvent(QKeyEvent* e) {
    //qDebug() << e->key();
    //qDebug() << e->text();
    if(e->text() == "a") {
        FaceObject& fo = TagedElements.at(selectedFace);
        fo.x = fo.x - 1;
    }
    if(e->text() == "d") {
        FaceObject& fo = TagedElements.at(selectedFace);
        fo.x = fo.x + 1;
    }
    if(e->text() == "s") {
        FaceObject& fo = TagedElements.at(selectedFace);
        fo.y = fo.y + 1;
    }
    if(e->text() == "w") {
        FaceObject& fo = TagedElements.at(selectedFace);
        fo.y = fo.y - 1;
    }
    if(e->text() == "A") {
        FaceObject& fo = TagedElements.at(selectedFace);
        fo.width = fo.width - 1;
    }
    if(e->text() == "D") {
        FaceObject& fo = TagedElements.at(selectedFace);
        fo.width = fo.width + 1;
    }
    if(e->text() == "S") {
        FaceObject& fo = TagedElements.at(selectedFace);
        fo.height = fo.height + 1;
    }
    if(e->text() == "W") {
        FaceObject& fo = TagedElements.at(selectedFace);
        fo.height = fo.height - 1;
    }
}
