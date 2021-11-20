#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bgmusic *bgm = new bgmusic();
    bgm->run();

    ui->label_register->installEventFilter(this);
    ui->label_findPassword->installEventFilter(this);
    //QMessageBox::warning(NULL, "Warning", "请更改database.cpp中的绝对路径");
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->label_register)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent->button() == Qt::LeftButton)
            {
                //QMessageBox::information(NULL, "qwer", uname);
                RegisterWindow* r = new RegisterWindow();
                r->show();
                return true;
            }
        }
        else
        {
            return false;
        }

    }
    else if (obj == ui->label_findPassword)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent->button() == Qt::LeftButton)
            {
//                QMessageBox::information(NULL, "Tip", "请联系管理员ghj@1930.com");
                ForgetPasswordWindow* fp = new ForgetPasswordWindow();
                fp->show();
                return true;
            }
        }
        else
        {
            return false;
        }

    }

    return QMainWindow::eventFilter(obj, event);


}

void MainWindow::on_pushButton_clicked()
{
    QString un, ps, tempps;
    un = ui->lineEdit->text();
    ps = ui->lineEdit_2->text();
    db = new Database();
    tempps = db->getUserInfoPassword(un);
    if(ps == tempps){
//        QMessageBox::information(NULL, "Tip", "登陆成功!");
        this->close();
        initWindow* i = new initWindow(un);
        i->show();
    }else{
        QMessageBox::warning(NULL, "Warning", "登陆失败!");
    }
}
