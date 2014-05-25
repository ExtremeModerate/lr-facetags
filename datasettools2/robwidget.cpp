#ifndef ROBWIDGET_H
#include "robwidget.h"
#endif // ROBWIDGET_H

RobWidget::RobWidget(QWidget *parent)
    : QWidget(parent)
{
    rubberBand = 0;
    displayImageLable = 0;

    // display a default image in this example
    displayImageOrigin.load("datasettools80.png");
    displayImage = displayImageOrigin;
    this->scaleDisplayImage();
}

void RobWidget::mousePressEvent(QMouseEvent *event){

    origin = event->pos();
        if (!rubberBand)
            rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
        rubberBand->setGeometry(QRect(origin, QSize()));
        rubberBand->show();

    }

    void RobWidget::mouseMoveEvent(QMouseEvent *event)
    {
        rubberBand->setGeometry(QRect(origin, event->pos()).normalized());
    }

    void RobWidget::mouseReleaseEvent(QMouseEvent *)
    {
        //rubberBand->hide();
        // determine selection, for example using QRect::intersects()
        // and QRect::contains().
    }

    void RobWidget::resizeEvent(QResizeEvent *)
    {
        //fprintf(stderr, "Resize RobWidged\n");
        this->scaleDisplayImage();
    }


 void RobWidget::scaleDisplayImage() {
        int max = this->height();
        if(this->width() < max) {
            max = this->width();
        }
        displayImage = displayImageOrigin.scaledToHeight(max,Qt::SmoothTransformation);

        if(displayImageLable != 0) {
        displayImageLable->setPixmap(QPixmap::fromImage(displayImage));
        }
    }

 void RobWidget::setLable(QLabel *lable) {
     this->displayImageLable = lable;
     scaleDisplayImage();
 }
