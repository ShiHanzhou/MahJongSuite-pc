#include "rulewindow.h"
#include "ui_rulewindow.h"

RuleWindow::RuleWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RuleWindow)
{
    ui->setupUi(this);

    QPalette palette=ui->textBrowser->palette();
    palette.setColor(QPalette::Base, QColor(0x00,0xff,0x00,0x00));
    ui->textBrowser->setPalette(palette);
    ui->textBrowser->setStyleSheet("QTextBrowser{border-width:0;border-style:outset}");
}

RuleWindow::~RuleWindow()
{
    delete ui;
}
