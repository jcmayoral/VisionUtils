#ifndef SECONDARYWINDOW_H
#define SECONDARYWINDOW_H

#include <QWidget>

namespace Ui {
class SecondaryWindow;
}

class SecondaryWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SecondaryWindow(QWidget *parent = 0);
    ~SecondaryWindow();

private:
    Ui::SecondaryWindow *ui;
};

#endif // SECONDARYWINDOW_H
