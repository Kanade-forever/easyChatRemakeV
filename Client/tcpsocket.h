#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>

#include <QFile>
#include <QTcpSocket>
#include <QFileDialog>
#include "message.h"
#include <QDebug>


class tcpsocket : public QObject
{
    Q_OBJECT
public:
    explicit tcpsocket(QObject *parent = nullptr);
    void runTcpSocket();

    void messageSend(Message &message);
    void tcpConnect(QString ipAddress = "127.0.0.1");
    void tcpDisConnect();
signals:
    void socketReceiveMessage(Message &message);

public slots:
    void onConnected();
    void onDisConnected();
    void onReadyRead();
    void onError(QAbstractSocket::SocketError socketError);
private:
    QTcpSocket socket;

};

#endif // TCPSOCKET_H
