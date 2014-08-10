#ifndef PLOTDIALOG_H
#define PLOTDIALOG_H

#include <QDialog>

namespace Ui {
class PlotDialog;
}

class PlotDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit PlotDialog(QWidget *parent = 0);
    ~PlotDialog();
    void addGraph(QVector<double> pr, QVector<double> rc, const QString &name);
    void plotGraphs();
    
private:
    Ui::PlotDialog *ui;
    int iNumGraph;
};

#endif // PLOTDIALOG_H
