#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QStack>

class Database{
    QSqlDatabase db1;
public:
    Database();

    QString getUserInfoUserName(int id);
    QString getUserInfoPassword(int id);
    QString getUserInfoPassword(QString username);
    QString getUserInfoEmail(QString username);
    int getUserInfoFeature(int id);
    int registerUser(int id, QString username, QString password, QString email);
    int registerUser(int id, QString username, QString password, QString email, int feature);
    int loginUser(QString username, QString password);
    int forgetPassword(QString username, int feature);
    int getMaxId();
    int updateUserInfoPassword(QString username, QString password);

    QString getRankUserName(int id);
    int getRankPoint(int id);
    int updateRankInfo(QString username, int point);
};

#endif // DATABASE_H
