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

    Manager::exemplar()->addObjectClicked(ui->imageWidget, type, ui->object_id->text(), trunc, occluded);

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
