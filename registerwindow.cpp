#include "registerwindow.h"
#include "ui_registerwindow.h"

RegisterWindow::RegisterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
    ui->label_returnLogin->installEventFilter(this);
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

bool RegisterWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = reinterpret_cast<QMouseEvent*>(event);
        if(mouseEvent->button() == Qt::LeftButton)
        {
            if(obj == ui->label_returnLogin)
            {
                this->close();

            }
            return true;

        }
    }
    return false;
}

// min:随机数的最小值，max:随机数的最大值
int RegisterWindow::generateRandomInteger(int min, int max)
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

void RegisterWindow::on_pushButton_clicked()
{
    if(ui->lineEdit->text().contains('@')){
        pin = generateRandomInteger(1000, 9999);
        Smtp smtp("MahJongSuiteGM@111.com", "qQgnhWYMeJEEguyj");
        QString tipStr;
        tipStr.append("尊敬的MahJongSuite用户您好，您请求的验证码为：");
        tipStr.append(QString::number(pin));
        smtp.send(ui->lineEdit->text().toUtf8(), "MahJongSuite注册验证", tipStr);
        QMessageBox::information(NULL, "Success", "发送成功！请注意查收");
    }else{
        QMessageBox::warning(NULL, "Error", "邮箱格式有误，请检查后重试。");
    }

}

void RegisterWindow::on_pushButton_2_clicked()
{
    if(ui->lineEdit_4->text() == "" || ui->lineEdit_3->text() == ""){
        QMessageBox::warning(NULL, "Error", "信息好像还没填全，检查重试下吧。");
    }else if(ui->lineEdit_2->text() == ""){
        QMessageBox::warning(NULL, "Error", "请输入验证码");
    }else if(ui->lineEdit_2->text().toInt() != pin){
        QMessageBox::warning(NULL, "Error", "验证码输入错误！");
    }else{
        db = new Database();
        int judge = 99;
        judge = db->registerUser(db->getMaxId() + 1, ui->lineEdit_4->text(), ui->lineEdit_3->text(), ui->lineEdit->text());
        if(judge == -1){
            QMessageBox::warning(NULL, "Error", "注册失败，用户名已被注册，请修改后重试。");
        }else{
            QMessageBox::information(NULL, "Congratulation", "恭喜您！注册成功。尽情享受MahJongSuite的游戏魅力吧！");
            this->close();
        }
    }
}
