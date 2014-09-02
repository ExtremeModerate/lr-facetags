#ifndef BBDIALOG_H
#define BBDIALOG_H

#include <QDialog>

namespace Ui {
class BBdialog;
}

class BBdialog : public QDialog
{
    Q_OBJECT
    QString imageFolder;
    
public:
    explicit BBdialog(QString path, QStringList classifiers, QWidget *parent = 0);
    ~BBdialog();
    void drawBBs(QImage &img, QString sFaceObjectFile, QRgb color);
    void drawRect(QImage &img, double x, double y, double w, double h, QRgb color);
    int iNumColors;

private slots:
    void showImage();
    
private:
    Ui::BBdialog *ui;
};

#endif // BBDIALOG_H
