#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QStringList>

namespace Ui {
class PlotWindow;
}


class PlotWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlotWindow(QWidget *parent = 0);
    void addData(double x, int index);
    void addGraph(QString name, QColor c);
    void setIsInitialized(bool a);
    bool getIsInitialized();
    void setMainGraphIndex(int index);
    int getMainGraphIndex();
    ~PlotWindow();

private slots:
    void realtimeDataSlot();

    void on_select_graph_clicked();

private:
    Ui::PlotWindow *ui;
    QTimer dataTimer;
    QStringList observed_graphs_;
    std::vector<double> data_;
    int graph_number_;
    int main_graph_index_;
    bool isInitialized_;
};

#endif // PLOTWINDOW_H
