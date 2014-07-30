#ifndef TAGTRAININGSETDIALOG_H
#define TAGTRAININGSETDIALOG_H

#include <QDialog>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

namespace Ui {
class TagTrainingSetDialog;
}

class TagTrainingSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TagTrainingSetDialog(QWidget *parent = 0);
    ~TagTrainingSetDialog();
    void setImage(cv::Mat mat);
    int getTag();

private:
    Ui::TagTrainingSetDialog *ui;
};

#endif // TAGTRAININGSETDIALOG_H
