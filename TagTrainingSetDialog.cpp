#include "TagTrainingSetDialog.h"
#include "ui_TagTrainingSetDialog.h"


TagTrainingSetDialog::TagTrainingSetDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::TagTrainingSetDialog) {
  ui->setupUi(this);
}

TagTrainingSetDialog::~TagTrainingSetDialog() {
  delete ui;
}

void TagTrainingSetDialog::setImage(cv::Mat mat) {
  // 8-bits unsigned, NO. OF CHANNELS=1
  if(mat.type()==CV_8UC1){
    // Set the color table (used to translate colour indexes to qRgb values)
    QVector<QRgb> colorTable;
    for (int i=0; i<256; i++)
      colorTable.push_back(qRgb(i,i,i));
    // Copy input Mat
    const uchar *qImageBuffer = (const uchar*)mat.data;
    // Create QImage with same dimensions as input Mat
    QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
    img.setColorTable(colorTable);
    ui->labelImage->setPixmap(QPixmap::fromImage(img));
  }
  // 8-bits unsigned, NO. OF CHANNELS=3
  if(mat.type()==CV_8UC3) {
    // Copy input Mat
    const uchar *qImageBuffer = (const uchar*)mat.data;
    // Create QImage with same dimensions as input Mat
    QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
    img.rgbSwapped();
    ui->labelImage->setPixmap(QPixmap::fromImage(img));
  }
}

int TagTrainingSetDialog::getTag() {
  return ui->spinBoxID->value();
}
