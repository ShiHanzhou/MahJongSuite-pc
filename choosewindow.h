#ifndef CHOOSEWINDOW_H
#define CHOOSEWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QEvent>

#include "gamewindow.h"

namespace Ui {
class ChooseWindow;
}

class ChooseWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChooseWindow(QWidget *parent = nullptr);
    ChooseWindow(QString ustr);
    ~ChooseWindow();

private:
    Ui::ChooseWindow *ui;

    QString uname;

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void on_pushButton_clicked();
};

#endif // CHOOSEWINDOW_H
