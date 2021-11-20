#ifndef RANKWINDOW_H
#define RANKWINDOW_H

#include <QMainWindow>
#include "database.h"
#include <QDebug>

namespace Ui {
class rankWindow;
}

class rankWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit rankWindow(QWidget *parent = nullptr);
    ~rankWindow();

private:
    Ui::rankWindow *ui;
};

#endif // RANKWINDOW_H
