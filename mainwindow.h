#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "plotwindow.h"
#include <featuredetection/FD.h>
#include <calibration/Calibration.h>
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

    void on_calibration_button_clicked();

    void on_match_button_clicked();

    void on_exit_button_clicked();

    void on_Visualize_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    FaultDetection fd_;
    Calibration calibration_;
    PlotWindow plt;
    bool stopFlag_;

};

#endif // MAINWINDOW_H
