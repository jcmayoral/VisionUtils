    #include "plotwindow.h"
#include <iostream>
#include "ui_plotwindow.h"

PlotWindow::PlotWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlotWindow),
    graph_number_(-1), isInitialized_(false),
    main_graph_index_(0), data_(), threshold_(0.0),
    hessian_(400), matching_threshold_(0.10)
{
    ui->setupUi(this);
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->customPlot->xAxis->setTicker(timeTicker);
    ui->customPlot->axisRect()->setupFullAxesBox();
    ui->customPlot->yAxis->setRange(-0.2, 0.2);
    ui->customPlot->xAxis->setLabel(QString("Time"));
    ui->customPlot->yAxis->setLabel(QString("Value"));
    ui->customPlot->legend->setVisible(true);

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    dataTimer.start(0); // Interval 0 means to refresh as fast as possible
    ui->customPlot->replot();

    ui->graph_list_->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

void PlotWindow::setThreshold(double val){
    std::cout << "set " << val;
    threshold_ = val;
}

double PlotWindow::getThreshold(){
    return threshold_;
}

void PlotWindow::setHessian(double val){
    hessian_ = val;
}

double PlotWindow::getHessian(){
    return hessian_;
}

void PlotWindow::setMatchingThreshold(double val){
    matching_threshold_ = val;
}

double PlotWindow::getMatchingThreshold(){
    return matching_threshold_;
}


void PlotWindow::addGraph(QString name, QColor c){
    graph_number_++;
    ui->customPlot->addGraph();
    ui->customPlot->graph(graph_number_)->setPen(c);
    ui->customPlot->graph(graph_number_)->setName(name);
    ui->graph_list_->addItem(name);
    data_.push_back(0.0);
}

void PlotWindow::setIsInitialized(bool a){
    isInitialized_ = a;
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
}

bool PlotWindow::getIsInitialized(){
    return isInitialized_;
}

void PlotWindow::setMainGraphIndex(int index){
    main_graph_index_ = index;
}

int PlotWindow::getMainGraphIndex(){
    return main_graph_index_;
}

void PlotWindow::addData(double x, int index){
    data_.at(index) = x;
}

void PlotWindow::realtimeDataSlot()
{
  //ui->groupBox->setGeometry(0,0,this->width(),this->height());
  ui->customPlot->setGeometry(0,0,ui->groupBox->width(), ui->groupBox->height());
  ui->graph_list_->setGeometry(0,0,ui->centralwidget->width(),ui->graph_list_->height());
  static QTime time(QTime::currentTime());
  // calculate two new data points:
  double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
  static double lastPointKey = 0;
  if (key-lastPointKey > 0.002) // at most add point every 2 ms
  {
    // add data to lines:
    for(int i=0; i<= graph_number_;++i){
        ui->customPlot->graph(i)->addData(key, data_[i]);
    }
    ui->customPlot->graph(main_graph_index_)->rescaleValueAxis();
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

    if(graph_number_>=0){
        ui->statusbar->showMessage(
              QString("%1 FPS, Total Data points: %2")
              .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
              .arg(ui->customPlot->graph(0)->data()->size()+ui->customPlot->graph(1)->data()->size())
              , 0);
        lastFpsKey = key;
        frameCount = 0;
    }
  }
}

PlotWindow::~PlotWindow()
{
    std::cout<<"Plot Window Destroyed";
    delete ui;
}

void PlotWindow::on_select_graph_clicked()
{
    QList<QListWidgetItem*> list;
    list  = ui->graph_list_->selectedItems();

    for (int j=0; j<= this->graph_number_; j++){
        ui->customPlot->graph(j)->setVisible(false);
        for (int i=0; i< list.size();i++){
            QString str = list.at(i)->text();
            if (!QString::compare(str,ui->customPlot->graph(j)->name())){
                setMainGraphIndex(j);
                ui->customPlot->graph(j)->setVisible(true);
            }
        }
   }
}

void PlotWindow::on_doubleSpinBox_valueChanged(double arg1)
{
    setThreshold(arg1);
}

void PlotWindow::on_doubleSpinBox2_valueChanged(double arg1)
{
    setHessian(arg1);
}

void PlotWindow::on_doubleSpinBox_2_valueChanged(double arg1)
{
    setMatchingThreshold(arg1);
}
