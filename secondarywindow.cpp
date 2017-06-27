#include "secondarywindow.h"
#include "QPushButton"
#include "qwt_plot.h"
#include "qwt_plot_curve.h"


SecondaryWindow::SecondaryWindow(QWidget *parent) : QWidget(parent)
{
    //setFixedSize(100, 50);
    QPushButton* m_button = new QPushButton("Hello World", this);
    m_button->setGeometry(10, 10, 80, 30);
    show();
}

SecondaryWindow::~SecondaryWindow()
{

}
