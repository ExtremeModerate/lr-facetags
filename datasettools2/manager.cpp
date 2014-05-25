#ifndef ROBWIDGET_H
#include "manager.h"
#endif // ROBWIDGET_H


Manager* Manager::instanz = 0;


Manager* Manager::exemplar()
{
  if( instanz == 0 )
    instanz = new Manager();

  instanz->directorySelected = false;
  return instanz;


  // setui list elements
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
