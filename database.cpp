#include "database.h"
#include "mainwindow.h"
#include <QDebug>

Database::Database(){
    db1 = QSqlDatabase::addDatabase("QSQLITE", "connection1");

    //db1.setDatabaseName("C:/Users/Tony Guo/Desktop/MahJongSuite/MahJongSuite/database/1.db");//设置数据库
    db1.setDatabaseName("1.db");

    if(db1.open()){
        qDebug() << "db:okkkkkk";
    }else{
        qDebug() << "db:noooooooooooooooooooo";
    }
}

QString Database::getUserInfoUserName(int id){
    QSqlQuery qry(db1);
    QString sql;
    sql.append("select * from UserInfo where Id = '");  //Vertex
    sql.append(QString::number(id));
    sql.append(QString(QLatin1String("'")));
    if(qry.exec(sql)){
        if(qry.next()){
            //QMessageBox::information(NULL,"1234",qry.value(1).toString());
            return qry.value(1).toString();
        }else{
            return "Error1!";
        }
    }
    return "Error2!";
}

QString Database::getUserInfoPassword(int id){
    QSqlQuery qry(db1);
    QString sql;
    sql.append("select * from UserInfo where id = '");  //Vertex
    sql.append(QString::number(id));
    sql.append(QString(QLatin1String("'")));
    //QMessageBox::information(NULL,"1234",sql);
    if(qry.exec(sql)){
        if(qry.next()){
            //QMessageBox::information(NULL,"1234",QString::number(qry.value(2).toInt()));
            return qry.value(2).toString();
        }else{
            return "Error1!";
        }
    }
    return "Error2!";
}

QString Database::getUserInfoPassword(QString username){
    QSqlQuery qry(db1);
    QString sql;
    sql.append("select * from UserInfo where UserName = '");  //Vertex
    sql.append(username);
    sql.append(QString(QLatin1String("'")));
    //QMessageBox::information(NULL,"1234",sql);
    if(qry.exec(sql)){
        if(qry.next()){
            //QMessageBox::information(NULL,"1234",QString::number(qry.value(2).toInt()));
            return qry.value(2).toString();
        }else{
            return "Error1!";
        }
    }
    return "Error2!";
}

QString Database::getUserInfoEmail(QString username){
    QSqlQuery qry(db1);
    QString sql;
    sql.append("select * from UserInfo where UserName = '");  //Vertex
    sql.append(username);
    sql.append(QString(QLatin1String("'")));
    //QMessageBox::information(NULL,"1234",sql);
    if(qry.exec(sql)){
        if(qry.next()){
            //QMessageBox::information(NULL,"1234",QString::number(qry.value(2).toInt()));
            return qry.value(3).toString();
        }else{
            return "Error1!";
        }
    }
    return "Error2!";
}

int Database::getUserInfoFeature(int id){
    QSqlQuery qry(db1);
    QString sql;
    sql.append("select * from UserInfo where id = '");  //Vertex
    sql.append(QString::number(id));
    sql.append(QString(QLatin1String("'")));
    //QMessageBox::information(NULL,"1234",sql);
    if(qry.exec(sql)){
        if(qry.next()){
            //QMessageBox::information(NULL,"1234",QString::number(qry.value(3).toInt()));
            return qry.value(4).toInt();
        }else{
            return -1;
        }
    }
    return -2;
}

int Database::registerUser(int id, QString username, QString password, QString email){
    QSqlQuery qry(db1);
    qry.prepare("INSERT INTO UserInfo (Id,UserName,Password,EmailAddress,Feature)"" VALUES(:idd,:un,:pa,:em,:fe);");
    qry.bindValue(":idd", id);
    qry.bindValue(":un", username);
    qry.bindValue(":pa", password);
    qry.bindValue(":em", email);
    qry.bindValue(":fe", 1);
    if(qry.exec()){
        /*if(qry.next()){
            //QMessageBox::information(NULL,"1234",qry.value(4).toString());
            return qry.value(4).toString();
        }else{
            return "Error1!";
        }*/
        qDebug() << "reSucc";
        return 0;
    }
    return -1;
}

int Database::getMaxId(){
    QSqlQuery qry(db1);
    QString sql;
    sql.append("select max(Id) Id from UserInfo;");

    //QMessageBox::information(NULL,"1234",sql);
    if(qry.exec(sql)){
        if(qry.next()){
            //QMessageBox::information(NULL,"1234",qry.value(4).toString());
            qDebug() << qry.value(0).toInt();
            return qry.value(0).toInt();
        }else{
            return -1;
        }
    }
    return -2;
}

int Database::updateUserInfoPassword(QString username, QString password){
    QSqlQuery qry(db1);
    QString sql;
    sql.append("update UserInfo set Password = \'");
    sql.append(password);
    sql.append("\' where UserName = '");
    sql.append(username);
    sql.append(QString(QLatin1String("'")));
    if(qry.exec(sql)){
        return 0;
    }else{
        return -1;
    }
}

QString Database::getRankUserName(int id){
    QSqlQuery qry(db1);
    QString sql;
    sql.append("select * from Rank where Id = '");  //Vertex
    sql.append(QString::number(id));
    sql.append(QString(QLatin1String("'")));
    //QMessageBox::information(NULL,"1234",sql);
    if(qry.exec(sql)){
        if(qry.next()){
            //QMessageBox::information(NULL,"1234",QString::number(qry.value(2).toInt()));
            return qry.value(1).toString();
        }else{
            return "Error1!";
        }
    }
    return "Error2!";
}

int Database::getRankPoint(int id){
    QSqlQuery qry(db1);
    QString sql;
    sql.append("select * from Rank where Id = '");  //Vertex
    sql.append(QString::number(id));
    sql.append(QString(QLatin1String("'")));
    //QMessageBox::information(NULL,"1234",sql);
    if(qry.exec(sql)){
        if(qry.next()){
            //QMessageBox::information(NULL,"1234",QString::number(qry.value(3).toInt()));
            return qry.value(2).toInt();
        }else{
            return -1;
        }
    }
    return -2;
}

int Database::updateRankInfo(QString username, int point){
    int count = 0;
    bool change = false;

    QSqlQuery qry(db1);
    QString sql;
    QString temp;

    QStack<QString> sun;
    QStack<int> sp;

    for(int i = 5; i > 0; i--){
        sql = "";
        sql.append("select * from Rank where Id = '");
        sql.append(QString::number(i));
        sql.append(QString(QLatin1String("'")));
        if(qry.exec(sql)){
            if(qry.next()){
                count++;
                sun.push(qry.value(1).toString());
                sp.push(qry.value(2).toInt());
            }
        }
    }
    //qDebug() << count;
    for(int i = 0; i < 5; i++){
        if(point > sp.top() && !change){
            temp = "";
            temp.append("update Rank set UserName = \'");
            temp.append(username);
            temp.append("\', Point = \"");
            temp.append(QString::number(point));
            temp.append("\" where Id = ");
            temp.append(QString::number(i + 1));

            qry.exec(temp);

            change = true;
        }else{
            temp = "";
            temp.append("update Rank set UserName = \'");
            temp.append(sun.top());
            temp.append("\', Point = \"");
            temp.append(QString::number(sp.top()));
            temp.append("\" where Id = ");
            temp.append(QString::number(i + 1));

            qry.exec(temp);

            sun.pop();
            sp.pop();
        }

    }
    if(change){
        QMessageBox::information(NULL, "Congratulation!", "恭喜上榜！榜上有名，请移步排行榜查看！");
        return 0;
    }else{
        return 0;
    }
}

