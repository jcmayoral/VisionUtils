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
    double lastx,lasty,lastcov, currentpearson, lastpearson,lastcusum,currentcusum=0.0;

    fd_.start();

    if(!plt.getIsInitialized()){
        plt.addGraph(QString("Variance X"),QColor(255,0,0));
        plt.addGraph(QString("Variance Y"),QColor(0,255,0));
        plt.addGraph(QString("Covariance"),QColor(0,0,255));
        plt.addGraph(QString("Pearson Coefficient"),QColor(0,0,0));
        plt.addGraph(QString("SURF-Based Collision"),QColor(0,255,255));
        plt.addGraph(QString("SURF Feature Distance"),QColor(255,0,0));
        plt.addGraph(QString("Pearson-Based Collision"),QColor(255,0,255));
        plt.setMainGraphIndex(4);
        plt.setIsInitialized(true);
    }

    while(true){
        std::cout<< exit_request_;
        if(fd_.run()){
            lastx = (fd_.getVariance().x-lastx);
            lasty = (fd_.getVariance().y-lasty);
            lastcov = (fd_.getCovariance() - lastcov);
            currentpearson = (fd_.getPearson());

            plt.addData(lastx,0);
            plt.addData(lasty,1);
            plt.addData(lastcov,2);
            plt.addData(currentpearson,3);

            currentcusum += fd_.getCUSUM();
            plt.addData(currentcusum,5);

            if (fabs(currentcusum - lastcusum) <= 1e-1){
               plt.addData(1,4);
            }
            else{
               plt.addData(0,4);
            }

            if (fabs(currentpearson - lastpearson) < 0.1){
              plt.addData(0,6);
            }
            else{
              plt.addData(1,6);
           }
           lastcusum =  currentcusum;
           lastpearson = currentpearson;
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
}


void MainWindow::on_gui_button_pressed()
{
    plt.show();
}
