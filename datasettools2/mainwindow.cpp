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
        ui->imageWidget->displayImageOrigin.load(path + "/" + current->text());
        ui->imageWidget->scaleDisplayImage();
    }
}
