#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QFileDialog>
#include <manager.h>
#include <QString>

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

private:



};

#endif // MAINWINDOW_H
