#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "robwidget.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Manager::exemplar()->fileList = ui->listWidgetFiles;
    Manager::exemplar()->listObjects = ui->listObjects;

    ui->imageWidget->setLable(ui->label_image);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toolButton_clicked()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly);
    int result = dialog.exec();
    QString directory;
    if (result)
    {
        directory = dialog.selectedFiles()[0];
        Manager::exemplar()->setSelectedDirectory(directory);
    }
}

void MainWindow::on_listWidgetFiles_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    //qDebug() << current->text();
    //qDebug() << "test";

    QString path = Manager::exemplar()->selectedDirectory;

    if(current) {
        Manager::exemplar()->selectedFile = current->text();
        Manager::exemplar()->changeImage();
        ui->imageWidget->displayImageOrigin.load(path + "/" + current->text());
        ui->imageWidget->scaleDisplayImage();
    }
}

void MainWindow::on_pushButton_clicked()
{

    // face = 1; dontcareface = 2;
    ObjectType type = otFace;
    if(ui->type_dontCareFace->isChecked()) {
        type = otDontCareFace;
    }
    double trunc = (double) ui->truncated_bar->value() / (double) 100;

    //qDebug() << trunc;

    //0 = fully visible, 1 = partly occluded, 2 = largely occluded, 3 = unknown
    OcclusionLevel occluded = olUnknown;
    if(ui->occluded_visible->isChecked()) {
        occluded = olNotOccluded;
    }
    if(ui->occluded_largly->isChecked()) {
        occluded = olLargelyOccluded;
    }
    if(ui->occluded_partly->isChecked()) {
        occluded = olPartlyOccluded;
    }

    Manager::exemplar()->addObjectClicked(ui->imageWidget, type, ui->object_id->text(), trunc, occluded, ui->imageWidget->scaleRatio);

    ui->imageWidget->scaleDisplayImage();
}

void MainWindow::on_pushButton_2_clicked()
{
    QList<QListWidgetItem *> list = ui->listObjects->selectedItems();
    if(list.size() != 1) {

    } else {
        //ui->listObjects->remo
        Manager::exemplar()->removeElements(list);

    }
    qDeleteAll(ui->listObjects->selectedItems());
    ui->imageWidget->scaleDisplayImage();

    // write new reduced list of faces to disk
    Manager::exemplar()->saveFacesToDisk();
}

void MainWindow::on_object_id_textChanged(const QString &arg1)
{
    // show all faces allready taged with the id of the object_id field
    QString id = ui->object_id->text();

    std::vector<QPixmap> listCrops;

    QString dir_name = "/home/daniel/BaoDataBase/myDataBase";
    // collect all FaceObjects and imagees with the given id
    DIR *dir;
    struct dirent *ent;
    struct stat info;
    const char *c_str2 = dir_name.toLocal8Bit().data();
    if ((dir = opendir (c_str2)) != NULL) {
      /* print all the files and directories within directory */
      while ((ent = readdir (dir)) != NULL) {
          stat(ent->d_name, &info);
          //if(!S_ISDIR (info.st_mode)) {
            //qDebug() << ent->d_name;
            std::vector<FaceObject> list = readObjectFile(dir_name.toStdString() + "/.metaface/" + ent->d_name + ".txt");
            if(list.size() > 0) {
                for(std::vector<FaceObject>::iterator it = list.begin(); it != list.end(); ++it) {
                    FaceObject fo = *it;
                    if(fo.objectID == id.toStdString()) {
                        qDebug() << "found a face in:" << ent->d_name;
                        QPixmap * img = new QPixmap();
                        QString fileName = QString::fromStdString(ent->d_name);
                        img->load(dir_name + "/" + fileName);
                        //QPixmap::copy(int x, int y, int width, int height )
                        QPixmap imgCroped = img->copy(fo.x, fo.y, fo.width, fo.height);
                        listCrops.push_back(imgCroped);
                    }

                }
            }
      }
      closedir (dir);
    }

    // check how many croped faces are stored in the list
    qDebug() << "there are " << listCrops.size() << " store in the vector";



    //QString imgPath = "/home/daniel/facetag/datasettools2/datasettools80.png";
    //QImage *img = new QImage();
    //bool loaded = img->load(imgPath);
    //if (loaded)
    //{
        /*QTableWidgetItem *thumbnail = new QTableWidgetItem;
        thumbnail->setData(Qt::DecorationRole, QPixmap::fromImage(*img));

        //thumbnailsWidget->setColumnCount(3);
        //thumbnailsWidget->setRowCount(3);
        ui->tableIamges->setItem(0, 0, thumbnail);*/

        //w.setCentralWidget(thumbnailsWidget);
    //} else {
        //qDebug()<<"Image "<<imgPath<<" was not opened!";
   // }
        int row = 0;
        int colom = 0;
        for(std::vector<QPixmap>::iterator it = listCrops.begin(); it != listCrops.end(); ++it) {
            QPixmap pm = *it;
            pm = pm.scaledToHeight(80,Qt::SmoothTransformation);
            QTableWidgetItem *thumbnail = new QTableWidgetItem;
            thumbnail->setData(Qt::DecorationRole, pm);
            ui->tableIamges->setItem(colom, row, thumbnail);
            if(colom == 2) {
                row++;
                colom = 0;
            } else {
                row++;
            }
        }
}
