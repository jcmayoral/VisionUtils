#include "secondarywindow.h"
#include "qwt-qt4/qwt_plot.h"
#include "qwt-qt4/qwt_plot_curve.h"
#include "ui_secondarywindow.h"

SecondaryWindow::SecondaryWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SecondaryWindow)
{
    ui->setupUi(this);
    /*
    QwtPlot *qwtPlot;
    double x[100], y1[100]; // x and y values

    qwtPlot = new QwtPlot(parent);
    // add curves
    QwtPlotCurve *curve1 = new QwtPlotCurve("Curve 1");

    //getSomeValues(x, y1, y2);
    for (int i=0; i<100; i++){
        x[i] = 10;
        y1[i] = 10;
    }

    // copy the data into the curves
    curve1->setData(x, y1, 100);
    curve1->attach(qwtPlot);

    // finally, refresh the plot
    qwtPlot->replot();
    */

}

SecondaryWindow::~SecondaryWindow()
{
    delete ui;
}
