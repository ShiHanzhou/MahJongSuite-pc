#include "smtp.h"
#include <QDebug>

Smtp::Smtp(QByteArray username, QByteArray password)
{
 this->username = username;
 this->password = password;
}

void Smtp::send(QByteArray recvaddr, QString subject, QString content)
{
 this->recvaddr = recvaddr;
 this->subject = subject;
 this->content = content;

 QByteArray usernametmp = this->username;
 QByteArray recvaddrtmp = this->recvaddr;

 clientsocket = new QTcpSocket();

 // TODO:
 // 这里是 111 的 smtp 服务器，若用其他的邮箱，请修改此处;
 this->clientsocket->connectToHost("smtp.111.com", 25, QTcpSocket::ReadWrite);
 this->clientsocket->waitForConnected(1000);
 this->clientsocket->waitForReadyRead(1000);
 recvdata = clientsocket->readAll();
 qDebug() << recvdata;


 this->clientsocket->write("HELO smtp.111.com\r\n");
 this->clientsocket->waitForReadyRead(1000);
 recvdata = clientsocket->readAll();
 qDebug() << recvdata;

 this->clientsocket->write("AUTH LOGIN\r\n");
 this->clientsocket->waitForReadyRead(1000);
 recvdata = clientsocket->readAll();
 qDebug() << recvdata;

 this->clientsocket->write(username.toBase64().append("\r\n"));
 this->clientsocket->waitForReadyRead(1000);
 recvdata = clientsocket->readAll();
 qDebug() << recvdata;

 this->clientsocket->write(password.toBase64().append("\r\n"));
 this->clientsocket->waitForReadyRead(1000);
 recvdata = clientsocket->readAll();
 qDebug() << recvdata;

 this->clientsocket->write(mailfrom.append(usernametmp.append(">\r\n")));
 this->clientsocket->waitForReadyRead(1000);
 recvdata = clientsocket->readAll();
 qDebug() << recvdata;

 this->clientsocket->write(rcptto.append(recvaddrtmp.append(">\r\n")));
 this->clientsocket->waitForReadyRead(1000);
 recvdata = clientsocket->readAll();
 qDebug() << recvdata;

 this->clientsocket->write("DATA\r\n");
 this->clientsocket->waitForReadyRead(1000);
 recvdata = clientsocket->readAll();
 qDebug() << recvdata;

 usernametmp = this->username;
 recvaddrtmp = this->recvaddr;

 this->clientsocket->write(prefrom.append(usernametmp.append("\r\n")));
 this->clientsocket->write(preto.append(recvaddrtmp.append("\r\n")));
 this->clientsocket->write(presubject.append(subject.toLocal8Bit().append("\r\n")));
 this->clientsocket->write("MIME-Version: 1.0\r\n");
 this->clientsocket->write("Content-Type: multipart/mixed;boundary=@boundary@\r\n\r\n");

 QString con = "--@boundary@\r\nContent-Type: text/plain;charset=\"gb2312\"\r\n\r\n" + content;
 this->clientsocket->write(con.toLocal8Bit().append("\r\n"));

        // 发多封附件时，这部分循环;

 this->clientsocket->write("--@boundary@--End--\r\n.\r\n");

 this->clientsocket->waitForReadyRead(1000);
 recvdata = clientsocket->readAll();
 qDebug() << recvdata;

 this->clientsocket->write("quit\r\n");
 this->clientsocket->waitForReadyRead(1000);
 recvdata = clientsocket->readAll();
 qDebug() << recvdata;
}

Smtp::~Smtp()
{
 delete this->clientsocket;
}
