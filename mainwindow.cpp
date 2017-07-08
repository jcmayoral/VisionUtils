#include "mainwindow.h"
#include "secondarywindow.h"
#include "plotwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mvo_(), calibration_(), wdg(), plt()
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    cout <<"Main Window destructor";

}

void MainWindow::on_calibration_button_clicked()
{
    calibration_.Calibrate();

}

void MainWindow::on_match_button_clicked()
{
    mvo_.run();
}

void MainWindow::on_exit_button_clicked()
{
    delete this;
}

void MainWindow::on_Visualize_clicked(bool checked)
{
    if (checked){
        wdg.show();
        plt.show();
    }
    else{
        wdg.close();
        plt.close();
    }
}
