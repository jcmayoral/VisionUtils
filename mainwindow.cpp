#include "mainwindow.h"
#include "plotwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mvo_(), calibration_(), plt()
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
    while(true){
        mvo_.run();
        plt.addData(mvo_.getMeanPoint().x,0);
        plt.addData(mvo_.getMeanPoint().y,1);
        if (char(waitKey(10)) == 27){break;
        }
    }
    mvo_.stop();
}

void MainWindow::on_exit_button_clicked()
{
    delete this;
}

void MainWindow::on_Visualize_clicked(bool checked)
{
    if (checked){
        plt.show();
    }

    else{
        plt.close();
    }
}
