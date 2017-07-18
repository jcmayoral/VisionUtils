#include "plotwindow.h"
#include <iostream>
#include "ui_plotwindow.h"

PlotWindow::PlotWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlotWindow),
    data_{0,0}
{
    ui->setupUi(this);
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(QColor(255,0,0)));
    ui->customPlot->graph(0)->setName(QString("Variance X"));

    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setPen(QPen(QColor(0, 255, 0)));
    ui->customPlot->graph(1)->setName(QString("Variance Y"));

    ui->customPlot->addGraph(); // red line
    ui->customPlot->graph(2)->setPen(QPen(QColor(0,0,255)));
    ui->customPlot->graph(2)->setName(QString("Covariance"));


    ui->customPlot->addGraph(); //
    ui->customPlot->graph(3)->setPen(QPen(QColor(0,255,255)));
    ui->customPlot->graph(3)->setName(QString("Pearson"));

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->customPlot->xAxis->setTicker(timeTicker);
    ui->customPlot->axisRect()->setupFullAxesBox();
    ui->customPlot->yAxis->setRange(-0.2, 0.2);
    ui->customPlot->xAxis->setLabel(QString("Time"));
    ui->customPlot->yAxis->setLabel(QString("Variance"));
    ui->customPlot->legend->setVisible(true);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(0); // Interval 0 means to refresh as fast as possible
    ui->customPlot->replot();
}

void PlotWindow::addData(double x, int index){
    data_[index] = x;
}

void PlotWindow::realtimeDataSlot()
{
  ui->customPlot->setGeometry(0,0,this->width(), this->height());
  static QTime time(QTime::currentTime());
  // calculate two new data points:
  double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
  static double lastPointKey = 0;
  if (key-lastPointKey > 0.002) // at most add point every 2 ms
  {
    // add data to lines:
    ui->customPlot->graph(0)->addData(key, data_[0]);
    ui->customPlot->graph(1)->addData(key, data_[1]);
    ui->customPlot->graph(2)->addData(key, data_[2]);
    ui->customPlot->graph(3)->addData(key, data_[3]);
    // rescale value (vertical) axis to fit the current data:
    //ui->customPlot->graph(0)->rescaleValueAxis();
    //ui->customPlot->graph(1)->rescaleValueAxis(true);
    ui->customPlot->graph(3)->rescaleValueAxis();
    lastPointKey = key;
  }
  // make key axis range scroll with the data (at a constant range size of 8):
  ui->customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
  ui->customPlot->replot();

  // calculate frames per second:
  static double lastFpsKey;
  static int frameCount;
  ++frameCount;
  if (key-lastFpsKey > 2) // average fps over 2 seconds
  {
    ui->statusbar->showMessage(
          QString("%1 FPS, Total Data points: %2")
          .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
          .arg(ui->customPlot->graph(0)->data()->size()+ui->customPlot->graph(1)->data()->size())
          , 0);
    lastFpsKey = key;
    frameCount = 0;
  }
}

PlotWindow::~PlotWindow()
{
    std::cout<<"Plot Window Destroyed";
    delete ui;
}
