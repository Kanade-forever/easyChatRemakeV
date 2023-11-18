#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTcpSocket>
#include <QList>
#include <QMetaEnum>
#include "message.h"
#include <QDebug>

class tcpserver : public QObject
{
    Q_OBJECT
public:
    explicit tcpserver(QObject *parent = nullptr);
    void runTcpServer();

    void tcpServerSendMessage(Message &message);

signals:
    void tcpServerStatusUpdate(QString status);
    void tcpServerReceiveMessage(Message &message);

public slots:
    void onNewConnection();
    void onConnected();
    void onDisConnected();
    void onReadyRead();
    void onError(QAbstractSocket::SocketError socketError);
private:
    QTcpServer server;
    QList<QTcpSocket*> sockets;
};

#endif // TCPSERVER_H
