#include "mainwindow.h"
#include "plotwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
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
    double lastx,lasty,lastcov, lastpearson,lastcusum, last_blur=0.0;
    double cusum_, pearson_, blur_= 0.0;

    fd_.start();

    if(!plt.getIsInitialized()){
        plt.addGraph(QString("Variance X"),QColor(255,0,0));
        plt.addGraph(QString("Variance Y"),QColor(0,255,0));
        plt.addGraph(QString("Covariance"),QColor(0,0,255));
        plt.addGraph(QString("Pearson Coefficient"),QColor(0,0,0));
        plt.addGraph(QString("CUSUM"),QColor(255,0,0));
        plt.addGraph(QString("Laplacian Blur"),QColor(255,0,0));
        plt.addGraph(QString("Pearson-Based Collision"),QColor(255,0,255));
        plt.addGraph(QString("Surf Collision Detector"),QColor(0,255,255));
        plt.addGraph(QString("Laplacian Collision Detector"),QColor(0,255,255));
        plt.setMainGraphIndex(5);
        plt.setIsInitialized(true);
    }

    double current_threshold = plt.getThreshold();

    while(fd_.run()){
        current_threshold = plt.getThreshold();
        fd_.updateHessianThreshold(plt.getHessian());
        fd_.setMatchPercentage(plt.getMatchingThreshold());

        lastx += fd_.getVariance().x;
        lasty += fd_.getVariance().y;
        lastcov += fd_.getCovariance();
        cusum_ = fd_.getCUSUM();
        pearson_ += fd_.getPearson();
        blur_ = fd_.getBlur();

        plt.addData(lastx,0);
        plt.addData(lasty,1);
        plt.addData(lastcov,2);
        plt.addData(pearson_,3);
        plt.addData(cusum_,4);
        plt.addData(blur_,5);


        if (fabs(cusum_-lastcusum)  > current_threshold){
           plt.addData(1,7);
        }
        else{
           plt.addData(0,7);
        }

        if (fabs(pearson_-lastpearson) > current_threshold){
          plt.addData(1,6);
        }
        else{
          plt.addData(0,6);
        }

        if (fabs(blur_-last_blur) > current_threshold){
          plt.addData(1,8);
        }
        else{
          plt.addData(0,8);
        }
        lastcusum =  cusum_;
        lastpearson = pearson_;
        last_blur = blur_;
        cv::waitKey(10);
     }
    cout << "stop";
    fd_.stop();
    //this->close();
    delete this;
}

void MainWindow::on_gui_button_pressed()
{
    plt.show();
}

void MainWindow::on_stop_button_clicked()
{
    std::cout << "Exit Pressed";
    fd_.stopRequest();
    plt.close();
}
