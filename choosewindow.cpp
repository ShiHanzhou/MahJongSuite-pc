#include "choosewindow.h"
#include "ui_choosewindow.h"

ChooseWindow::ChooseWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChooseWindow)
{
    ui->setupUi(this);

    /*ui->label_1->installEventFilter(this);
    ui->label_2->installEventFilter(this);
    ui->label_3->installEventFilter(this);
    ui->label_4->installEventFilter(this);*/
}

ChooseWindow::ChooseWindow(QString ustr) :
    QMainWindow(),
    ui(new Ui::ChooseWindow)
{
    ui->setupUi(this);

    uname = ustr;

    ui->label_1->installEventFilter(this);
    ui->label_2->installEventFilter(this);
    ui->label_3->installEventFilter(this);
    ui->label_4->installEventFilter(this);
}

ChooseWindow::~ChooseWindow()
{
    delete ui;
}

bool ChooseWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->label_1)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent->button() == Qt::LeftButton)
            {
                //QMessageBox::information(NULL, "qwer", uname);
                GameWindow* g = new GameWindow(1, uname);
                g->show();
                return true;
            }
        }
        else
        {
            return false;
        }

    }
    else if (obj == ui->label_2)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent->button() == Qt::LeftButton)
            {
                GameWindow* g = new GameWindow(2, uname);
                g->show();
                return true;
            }
        }
        else
        {
            return false;
        }

    }
    else if (obj == ui->label_3)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent->button() == Qt::LeftButton)
            {
                GameWindow* g = new GameWindow(3, uname);
                g->show();
                return true;
            }
        }
        else
        {
            return false;
        }

    }
    else if (obj == ui->label_4)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent->button() == Qt::LeftButton)
            {
                GameWindow* g = new GameWindow(4, uname);
                g->show();
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

void ChooseWindow::on_pushButton_clicked()
{
    GameWindow* g = new GameWindow(1, uname);
    g->show();
}
