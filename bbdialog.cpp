#include "bbdialog.h"
#include "ui_bbdialog.h"

#include <QDir>
#include <QDirIterator>
#include <iostream>

#include "readWriteObjectFile.h"

BBdialog::BBdialog(QString path, QStringList classifiers, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BBdialog)
{
    ui->setupUi(this);
    connect(ui->listWidgetImages, SIGNAL(itemSelectionChanged()), this, SLOT(showImage()));
    connect(ui->listWidgetClassifier, SIGNAL(itemSelectionChanged()), this, SLOT(showImage()));

    imageFolder = path;
    iNumColors = 0;
    //ui->label_image->setScaledContents(true);

    // Fill classifier list
    ui->listWidgetClassifier->addItems(classifiers);

    // Fill image list
    QDir dirImgFolder(imageFolder);
    dirImgFolder.setFilter(QDir::Files);
    QDirIterator itDirImgFolder(dirImgFolder);
    while(itDirImgFolder.hasNext())
    {
        itDirImgFolder.next();
        ui->listWidgetImages->addItem(itDirImgFolder.fileName());
    }
    ui->listWidgetImages->sortItems();
}

BBdialog::~BBdialog()
{
    delete ui;
}

inline bool isIn(QImage &img, double x, double y)
{
    return x >= 0.0 && y >= 0.0 && x < img.width() && y < img.height();
}

void BBdialog::drawRect(QImage &img, double x, double y, double w, double h, QRgb color)
{
    for(int i=x; i<x+w; i++)
    {
        if(isIn(img,i,y))
            img.setPixel(i, y, color);
        if(isIn(img,i,y+h))
            img.setPixel(i, y+h, color);
    }
    for(int j=y; j<y+h; j++)
    {
        if(isIn(img,x,j))
            img.setPixel(x, j, color);
        if(isIn(img,x+w,j))
            img.setPixel(x+w, j, color);
    }
}

void BBdialog::drawBBs(QImage &img, QString sFaceObjectFile, QRgb color)
{
    std::vector<FaceObject> vfo = readObjectFile(sFaceObjectFile.toStdString());
    for(size_t i=0; i<vfo.size(); i++)
        drawRect(img, vfo[i].x, vfo[i].y, vfo[i].width, vfo[i].height, color);
}

void BBdialog::showImage()
{
    if(ui->listWidgetImages->selectedItems().size() < 1) return;
    QString imgFileName = ui->listWidgetImages->selectedItems().at(0)->text();
    QRgb green = qRgb(0, 255, 0);
    QRgb color = qRgb(255, 0, 0);
    QImage img(imageFolder+"/"+imgFileName);
    drawBBs(img, imageFolder+"/.metaface/"+imgFileName+".txt", green);
    if(ui->listWidgetClassifier->selectedItems().size() > 0)
        drawBBs(img, ui->listWidgetClassifier->selectedItems().at(0)->text()+"/"+imgFileName+".txt", color);
    img = img.scaled(ui->label_image->width(), ui->label_image->height(), Qt::KeepAspectRatio);
    ui->label_image->setPixmap(QPixmap::fromImage(img));
}
