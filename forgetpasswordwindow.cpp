#include "forgetpasswordwindow.h"
#include "ui_forgetpasswordwindow.h"

ForgetPasswordWindow::ForgetPasswordWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ForgetPasswordWindow)
{
    ui->setupUi(this);

    ui->label_btpl->installEventFilter(this);
}

ForgetPasswordWindow::~ForgetPasswordWindow()
{
    delete ui;
}

bool ForgetPasswordWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->label_btpl)
    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent->button() == Qt::LeftButton)
            {
                this->close();
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

// min:随机数的最小值，max:随机数的最大值
int ForgetPasswordWindow::generateRandomInteger(int min, int max)
{
    Q_ASSERT(min < max);
    // 加入随机种子。种子是当前时间距离0点0分0秒的秒数。
    // 每次启动程序，只添加一次种子，以做到数字真正随机。
    static bool seedStatus;
    if (!seedStatus)
    {
        qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
        seedStatus = true;
    }
    int nRandom = qrand() % (max - min);
    nRandom = min + nRandom;

    return nRandom;
}

void ForgetPasswordWindow::on_pushButton_clicked()
{
    if(ui->lineEdit_email->text().contains('@')){
        db = new Database();
        QString tempEmail = db->getUserInfoEmail(ui->lineEdit_un->text());
        if(tempEmail == ui->lineEdit_email->text()){
            //邮箱正确
            pin = generateRandomInteger(1000, 9999);
            Smtp smtp("MahJongSuiteGM@111.com", "qQgnhWYMeJEEguyj");
            QString tipStr;
            tipStr.append("尊敬的MahJongSuite用户您好，您请求的验证码为：");
            tipStr.append(QString::number(pin));
            smtp.send(ui->lineEdit_email->text().toUtf8(), "MahJongSuite密码找回验证", tipStr);
            QMessageBox::information(NULL, "Success", "发送成功！请注意查收");
        }else{
            QMessageBox::warning(NULL, "Error", "您输入的用户名与绑定邮箱不匹配，请查证后重试！");
            return;
        }
    }else{
        QMessageBox::warning(NULL, "Error", "邮箱格式有误，请检查后重试。");
        return;
    }
}

void ForgetPasswordWindow::on_pushButton_2_clicked()
{
    if(ui->lineEdit_un->text() == "" || ui->lineEdit_pw->text() == ""){
        QMessageBox::warning(NULL, "Error", "信息好像还没填全，检查重试下吧。");
    }else if(ui->lineEdit_pin->text() == ""){
        QMessageBox::warning(NULL, "Error", "请输入验证码");
    }else if(ui->lineEdit_pin->text().toInt() != pin){
        QMessageBox::warning(NULL, "Error", "验证码输入错误！");
    }else{
        db = new Database();
        int judge = 99;
        judge = db->updateUserInfoPassword(ui->lineEdit_un->text(), ui->lineEdit_pw->text());
        if(judge == -1){
            QMessageBox::warning(NULL, "Error", "未知错误");
        }else{
            QMessageBox::information(NULL, "Congratulation", "恭喜您！找回成功。尽情享受MahJongSuite的游戏魅力吧！");
            this->close();
        }
    }
}
