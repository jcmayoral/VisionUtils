#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "plotwindow.h"
#include <featuredetection/FD.h>
//#include <calibration/Calibration.h>
#include "qcustomplot/qcustomplot.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_match_button_clicked();

    void on_gui_button_pressed();

    void on_stop_button_clicked();

private:
    Ui::MainWindow *ui;
    FaultDetection fd_;
    PlotWindow plt;

};

#endif // MAINWINDOW_H
