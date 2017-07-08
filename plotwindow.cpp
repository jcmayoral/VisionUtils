#include "plotwindow.h"
#include <iostream>

#include "ui_plotwindow.h"

PlotWindow::PlotWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlotWindow)
{
    ui->setupUi(this);
}

PlotWindow::~PlotWindow()
{
    std::cout<<"Plot Window Destroyed";
    delete ui;
}
