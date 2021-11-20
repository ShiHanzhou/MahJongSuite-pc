#ifndef INITWINDOW_H
#define INITWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "gamewindow.h"
#include "choosewindow.h"
#include "rulewindow.h"
#include "rankwindow.h"

namespace Ui {
class initWindow;
}

class initWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit initWindow(QWidget *parent = nullptr);
    initWindow(QString ustr);
    ~initWindow();

private:
    Ui::initWindow *ui;

    QString uname;  // 用户名

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // INITWINDOW_H
