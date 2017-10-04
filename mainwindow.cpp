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
    double lastx,lasty,lastcov, currentpearson, lastpearson,lastcusum,currentcusum=0.0;
    double cusum_, pearson_ = 0.0;

    fd_.start();

    if(!plt.getIsInitialized()){
        plt.addGraph(QString("Variance X"),QColor(255,0,0));
        plt.addGraph(QString("Variance Y"),QColor(0,255,0));
        plt.addGraph(QString("Covariance"),QColor(0,0,255));
        plt.addGraph(QString("Pearson Coefficient"),QColor(0,0,0));
        plt.addGraph(QString("SURF Feature Distance"),QColor(255,0,0));
        plt.addGraph(QString("Pearson-Based Collision"),QColor(255,0,255));
        plt.addGraph(QString("SURF-Based Collision"),QColor(0,255,255));
        plt.setMainGraphIndex(4);
        plt.setIsInitialized(true);
    }

    double current_threshold = plt.getThreshold();

    while(fd_.run()){
        current_threshold = plt.getThreshold();

        lastx += fd_.getVariance().x;
        lasty += fd_.getVariance().y;
        lastcov += fd_.getCovariance();
        cusum_ += fd_.getCUSUM();
        pearson_ += fd_.getPearson();

        plt.addData(lastx,0);
        plt.addData(lasty,1);
        plt.addData(lastcov,2);
        plt.addData(pearson_,3);
        plt.addData(cusum_,4);

        //currentcusum = (currentcusum + fd_.getCUSUM())/2;
        //cusum_ += currentcusum;

        if (fabs(cusum_-lastcusum)  <= current_threshold){
           plt.addData(1,6);
        }
        else{
           plt.addData(0,6);
        }

        if (fabs(pearson_-lastpearson) < 10e-3){
          plt.addData(1,5);
        }
        else{
          plt.addData(0,5);
       }
       lastcusum =  cusum_;
       lastpearson = pearson_;
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
