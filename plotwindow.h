#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class PlotWindow;
}

class PlotWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlotWindow(QWidget *parent = 0);
    void addData(double x);
    ~PlotWindow();

private slots:
    void realtimeDataSlot();


private:
    Ui::PlotWindow *ui;
    QTimer dataTimer;
    double newSample_;
};

#endif // PLOTWINDOW_H
