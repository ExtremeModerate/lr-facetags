#ifndef ROBWIDGET_H
#define ROBWIDGET_H

#include <QMainWindow>
#include <QWidget>
#include <QMouseEvent>
#include <QRubberBand>
#include <string>
#include <QImage>
#include <QLabel>
#include <QPainter>
#include "manager.h"

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


    QRect getBandBox();
    double scaleRatio;

protected:
    virtual void resizeEvent(QResizeEvent *);


private:
    QRubberBand *rubberBand;
    QPoint origin;

    QImage displayImage;
    QLabel *displayImageLable;

    QPoint mousePos;


};

#endif // ROBWIDGET_H
