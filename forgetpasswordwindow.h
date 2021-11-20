#ifndef FORGETPASSWORDWINDOW_H
#define FORGETPASSWORDWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QEvent>
#include "smtp.h"
#include <QMessageBox>
#include <QTime>
#include "database.h"

namespace Ui {
class ForgetPasswordWindow;
}

class ForgetPasswordWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ForgetPasswordWindow(QWidget *parent = nullptr);
    ~ForgetPasswordWindow();

private:
    Ui::ForgetPasswordWindow *ui;

    Database *db;

    int pin; //验证码

    int generateRandomInteger(int min, int max);

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // FORGETPASSWORDWINDOW_H
