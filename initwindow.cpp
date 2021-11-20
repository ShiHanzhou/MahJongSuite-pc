#include "initwindow.h"
#include "ui_initwindow.h"


initWindow::initWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::initWindow)
{
    ui->setupUi(this);
}

initWindow::initWindow(QString ustr) :
    QMainWindow(),
    ui(new Ui::initWindow)
{
    ui->setupUi(this);

    uname = ustr;

    ui->label_begin->installEventFilter(this);
    ui->label_rank->installEventFilter(this);
    ui->label_rule->installEventFilter(this);
}

initWindow::~initWindow()
{
    delete ui;
}

bool initWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->label_begin)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent->button() == Qt::LeftButton)
            {
                ChooseWindow* c = new ChooseWindow(uname);
                c->show();
                return true;
            }
        }
        else
        {
            return false;
        }

    }
    else if (obj == ui->label_rank)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent->button() == Qt::LeftButton)
            {
                rankWindow* r = new rankWindow();
                r->show();
                return true;
            }
        }
        else
        {
            return false;
        }

    }
    else if (obj == ui->label_rule)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent->button() == Qt::LeftButton)
            {
                RuleWindow* r = new RuleWindow();
                r->show();
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
