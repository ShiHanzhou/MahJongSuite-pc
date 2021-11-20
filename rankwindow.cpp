#include "rankwindow.h"
#include "ui_rankwindow.h"

rankWindow::rankWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::rankWindow)
{
    ui->setupUi(this);

    Database *db = new Database();
    ui->label_2nd_5->setText(db->getRankUserName(1));
    ui->label_2nd_4->setText(QString::number(db->getRankPoint(1)));
    ui->label_2nd_2->setText(db->getRankUserName(2));
    ui->label_2nd_3->setText(QString::number(db->getRankPoint(2)));
    ui->label_3rd_2->setText(db->getRankUserName(3));
    ui->label_3rd_3->setText(QString::number(db->getRankPoint(3)));
    ui->label_4th_2->setText(db->getRankUserName(4));
    ui->label_4th_3->setText(QString::number(db->getRankPoint(4)));
    ui->label_5th_2->setText(db->getRankUserName(5));
    ui->label_5th_3->setText(QString::number(db->getRankPoint(5)));
    //ui->label_2nd_5->setText(db->getRankUserName(1));
    //qDebug() << db->getVName(2);
}

rankWindow::~rankWindow()
{
    delete ui;
}
