#include "plotdialog.h"
#include "ui_plotdialog.h"

PlotDialog::PlotDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlotDialog)
{
    ui->setupUi(this);
    iNumGraph = -1;
    iNumColor = -1;
}

PlotDialog::~PlotDialog()
{
    delete ui;
}

void PlotDialog::addGraph(QVector<double> pr, QVector<double> rc, const QString &name)
{
    iNumGraph++;
    iNumColor++;
    if(iNumColor%10 == 12-7) iNumColor++; // Do not use yellow
    //printf("iNumGraph=%d\n",iNumGraph);
    ui->customPlot->addGraph();
    ui->customPlot->graph(iNumGraph)->setData(rc, pr);
    ui->customPlot->graph(iNumGraph)->setPen(QPen((Qt::GlobalColor)(7+(iNumColor%10)))); // Use colors 7..18 of Qt::GlobalColor
    ui->customPlot->graph(iNumGraph)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssPlus, (Qt::GlobalColor)(7+(iNumColor%10)), 8));
    ui->customPlot->graph(iNumGraph)->setName(name);
}

void PlotDialog::plotGraphs()
{
    // Legend
    ui->customPlot->legend->setVisible(true);
    QCPLayoutGrid *subLayout = new QCPLayoutGrid();
    QCPLayoutElement *dummyElement = new QCPLayoutElement();
    ui->customPlot->plotLayout()->addElement(0, 1, subLayout);
    subLayout->addElement(0, 0, ui->customPlot->legend);
    subLayout->addElement(1, 0, dummyElement);
    subLayout->setRowStretchFactor(0, 0.01);
    ui->customPlot->plotLayout()->setColumnStretchFactor(1, 0.01);

    // Axes
    ui->customPlot->xAxis->setLabel("Recall");
    ui->customPlot->yAxis->setLabel("Precision");
    ui->customPlot->xAxis->setRange(0, 1);
    ui->customPlot->yAxis->setRange(0, 1);
    ui->customPlot->xAxis->setAutoTickStep(false);
    ui->customPlot->yAxis->setAutoTickStep(false);
    ui->customPlot->xAxis->setTickStep(0.1);
    ui->customPlot->yAxis->setTickStep(0.1);
    ui->customPlot->replot();
}
