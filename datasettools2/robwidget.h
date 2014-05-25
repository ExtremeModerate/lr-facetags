#ifndef ROBWIDGET_H
#define ROBWIDGET_H

#include <QMainWindow>
#include <QWidget>
#include <QMouseEvent>
#include <QRubberBand>
#include <string>
#include <QImage>
#include <QLabel>
#include "mainwindow.h"

class RobWidget : public QWidget
{

public:
    RobWidget(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void setLable(QLabel *lable);
    QImage displayImageOrigin;
    void scaleDisplayImage();

protected:
    virtual void resizeEvent(QResizeEvent *);


private:
    MainWindow *mainWindow;
    QRubberBand *rubberBand;
    QPoint origin;

    QImage displayImage;
    QLabel *displayImageLable;

};

#endif // ROBWIDGET_H
