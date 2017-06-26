#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mvo_(), calibration_()
{
    //connect(this->ui->Visualize, SIGNAL(click()), this, SLOT(on_Visualize_clicked()));
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
    wdg = new SecondaryWindow();
    if (checked){
        wdg->show();
    }
    else{
        wdg->hide();
    }
}
