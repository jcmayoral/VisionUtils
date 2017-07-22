#include "mainwindow.h"
#include "plotwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    exit_request_(false)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    cout <<"Main Window destructor";
}

void MainWindow::on_match_button_clicked()
{
    double lastx,lasty,lastcov,lastpearson=0.0;

    fd_.start();

    if(!plt.getIsInitialized()){
        plt.addGraph(QString("Variance X"),QColor(255,0,0));
        plt.addGraph(QString("Variance Y"),QColor(0,255,0));
        plt.addGraph(QString("Covariance"),QColor(0,0,255));
        plt.addGraph(QString("Pearson Coefficient"),QColor(255,255,0));
        plt.addGraph(QString("Collision State"),QColor(0,255,255));
        plt.addGraph(QString("Experiment"),QColor(255,0,0));
        plt.setMainGraphIndex(5);
        plt.setIsInitialized(true);
    }

    while(true){
        std::cout<< exit_request_;
        if(fd_.run()){
            lastx = (fd_.getVariance().x-lastx);
            lasty = (fd_.getVariance().y-lasty);
            lastcov = (fd_.getCovariance() - lastcov);
            lastpearson = (fd_.getPearson());

            plt.addData(lastx,0);
            plt.addData(lasty,1);
            plt.addData(lastcov,2);
            plt.addData(lastpearson,3);
            plt.addData(fd_.getCUSUM(),5);

            if (fabs(lastpearson)>1e-10){
               plt.addData(1,4);
            }
            else{
               plt.addData(0,4);
            }
        }
        cv::waitKey(10);
        if (exit_request_){break;}
    }
    fd_.stop();
}

void MainWindow::on_exit_button_clicked()
{
    this->close();
    plt.close();
    exit_request_ = true;
    std::cout << "exit outside " << std::endl;
}


void MainWindow::on_gui_button_pressed()
{
    plt.show();
    std::cout << "activate";

}
