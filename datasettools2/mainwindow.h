#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QFileDialog>
#include <manager.h>
#include <QString>
#include "FaceObject.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;


private slots:
    void on_toolButton_clicked();

    void on_listWidgetFiles_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_object_id_textChanged(const QString &arg1);

    void on_listObjects_currentRowChanged(int currentRow);

private:



};

#endif // MAINWINDOW_H
