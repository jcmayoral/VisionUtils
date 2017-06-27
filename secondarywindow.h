#ifndef SECONDARYWINDOW_H
#define SECONDARYWINDOW_H

#include <QWidget>
#include <qwt-qt4/qwt_plot.h>
#include <qwt-qt4/qwt_plot_curve.h>

class SecondaryWindow : public QWidget
{
    Q_OBJECT

public:
    SecondaryWindow();
    ~SecondaryWindow();

private:
    QwtPlot *qwtPlot;
    QwtPlotCurve *curve1;

};

#endif // SECONDARYWINDOW_H
