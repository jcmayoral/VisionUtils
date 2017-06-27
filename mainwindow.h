#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "secondarywindow.h"
#include <monocularvision/MVO.h>
#include <calibration/Calibration.h>
#include <gui/GUI.h>

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
    MVO mvo_;
    Calibration calibration_;
    //SecondaryWindow *wdg;

};

#endif // MAINWINDOW_H
