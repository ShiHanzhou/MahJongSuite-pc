#include "mylabel.h"

MyLabel::MyLabel(QWidget* parent) :QLabel(parent)
{

}
MyLabel::~MyLabel()
{

}
void MyLabel::enterEvent(QEvent *e)
{
    if(this->objectName()=="label_begin")
    {
        setPixmap(QPixmap(":/new/prefix1/pic/newbegin.png"));
    }
    if(this->objectName()=="label_rank")
    {
        setPixmap(QPixmap(":/new/prefix1/pic/newrank.png"));
    }
    if(this->objectName()=="label_rule")
    {
        setPixmap(QPixmap(":/new/prefix1/pic/newrule.png"));
    }
    if(this->objectName()=="label_1")
    {
        setPixmap(QPixmap(":/new/prefix1/pic/newdiff1.png"));
    }
    if(this->objectName()=="label_2")
    {
        setPixmap(QPixmap(":/new/prefix1/pic/newdiff2.png"));
    }
    if(this->objectName()=="label_3")
    {
        setPixmap(QPixmap(":/new/prefix1/pic/newdiff3.png"));
    }
    if(this->objectName()=="label_4")
    {
        setPixmap(QPixmap(":/new/prefix1/pic/newdiff4.png"));
    }
}
void MyLabel::leaveEvent(QEvent *e)
{
    if(this->objectName()=="label_begin")
    {
        setPixmap(QPixmap(":/new/prefix1/pic/begin.png"));
    }
    if(this->objectName()=="label_rank")
    {
        setPixmap(QPixmap(":/new/prefix1/pic/rank.png"));
    }
    if(this->objectName()=="label_rule")
    {
        setPixmap(QPixmap(":/new/prefix1/pic/rule.png"));
    }
    if(this->objectName()=="label_1")
    {
        setPixmap(QPixmap(":/new/prefix1/pic/difficulty1.png"));
    }
    if(this->objectName()=="label_2")
    {
        setPixmap(QPixmap(":/new/prefix1/pic/difficulty2.png"));
    }
    if(this->objectName()=="label_3")
    {
        setPixmap(QPixmap(":/new/prefix1/pic/difficulty3.png"));
    }
    if(this->objectName()=="label_4")
    {
        setPixmap(QPixmap(":/new/prefix1/pic/difficulty4.png"));
    }
}
