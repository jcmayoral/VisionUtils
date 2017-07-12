#include "mainwindow.h"
#include "plotwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    fd_(), calibration_(), plt()
{
    ui->setupUi(this);
    fd_.start();
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
    double lastx,lasty,lastcov=0.0;
    double length = 0.0;

    while(true){
        if(fd_.run()){           
            length = std::sqrt(std::pow(fd_.getVariance().x,2) + std::pow(fd_.getVariance().y,2));
            lastx = (fd_.getVariance().x-lastx);
            lasty = (fd_.getVariance().y-lasty);
            lastcov = (fd_.getCovariance() - lastcov);

            if (length > 1e-10){
                lastx/=length;
                lasty/=length;
                lastcov/=length;
            }

            plt.addData(lastx,0);
            plt.addData(lasty,1);
            plt.addData(lastcov,2);
            //last = fd_.getMeanPoint();
            //plt.addData(fd_.getVariance().x,0);
            //plt.addData(fd_.getVariance().y,1);
        }
        if (char(waitKey(10)) == 27){break;
        }
    }
    fd_.stop();
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
