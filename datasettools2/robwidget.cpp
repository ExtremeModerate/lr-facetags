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
        mousePos = event->pos();
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

        // save scale ratio
        scaleRatio = (double)max / (double) displayImageOrigin.height();
        //fprintf(stderr, "Resize RobWidged %f \n", scaleRatio);

        displayImage = displayImageOrigin.scaledToHeight(max,Qt::SmoothTransformation);

        if(displayImageLable != 0) {

            /// add all boxes to the image
            QPixmap pixma = QPixmap::fromImage(displayImage);
            /*QPainter qPainter(&pixma);
            qPainter.setBrush(Qt::NoBrush);
            qPainter.setPen(Qt::red);
            //qPainter.drawRect(*x);
            qPainter.drawRect(10,10,100,100);
            */
            Manager::exemplar()->frameAllFaces(&pixma, this->scaleRatio);



            displayImageLable->setPixmap(pixma);


            //displayImageLable->setPixmap(QPixmap::fromImage(displayImage));
        }
    }

 void RobWidget::setLable(QLabel *lable) {
     this->displayImageLable = lable;
     scaleDisplayImage();
 }

 QRect RobWidget::getBandBox() {
     QRect * x = new QRect(origin,mousePos);
     QRect * xScaled = new QRect((int)(x->x() * scaleRatio), (int)(x->y() * scaleRatio), (int)(x->width() * scaleRatio), (int)(x->height() * scaleRatio));

     return *xScaled;
 }

 /*QPixmap RobWidget::addImageBox() {
     QPixmap pixma = QPixmap::fromImage(displayImage);
     QPainter qPainter(&pixma);
     qPainter.setBrush(Qt::NoBrush);
     qPainter.setPen(Qt::red);
     qPainter.drawRect(*x);
     //displayImageLable->setPixmap(pixma);
 }*/
