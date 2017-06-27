#include "secondarywindow.h"
#include "qwt-qt4/qwt_plot.h"
#include "qwt-qt4/qwt_plot_curve.h"

SecondaryWindow::SecondaryWindow()
{
    double x[100], y[100]; // x and y values
/*
    qwtPlot = new QwtPlot;
    curve1 = new QwtPlotCurve;

    //getSomeValues(x, y1, y2);
    for (int i=0;i<100;i++){
        x[i] = i;
        y[i] = i;
    }
    // copy the data into the curves
    curve1->setData(x, y, 100);

    curve1->attach(qwtPlot);

    // finally, refresh the plot
    qwtPlot->replot();
*/
}

SecondaryWindow::~SecondaryWindow()
{

}
