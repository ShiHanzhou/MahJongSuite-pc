#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include "smtp.h"
#include <QMessageBox>
#include <QTime>
#include "database.h"

namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = nullptr);
    ~RegisterWindow();

private:
    Ui::RegisterWindow *ui;

    Database *db;

    int pin; //验证码

    int generateRandomInteger(int min, int max);

protected:
    bool eventFilter(QObject *obj, QEvent *event);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // REGISTERWINDOW_H
