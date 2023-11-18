#include "tcpsocket.h"

tcpsocket::tcpsocket(QObject *parent) : QObject(parent)
{

}

void tcpsocket::runTcpSocket()
{
    connect(&socket,&QTcpSocket::connected,
            this,&tcpsocket::onConnected);
    connect(&socket,&QTcpSocket::disconnected,
            this,&tcpsocket::onDisConnected);
    connect(&socket,&QTcpSocket::readyRead,
            this,&tcpsocket::onReadyRead);
    connect(&socket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(onError(QAbstractSocket::SocketError)));

}

void tcpsocket::messageSend(Message &message)
{
    QByteArray data;
    QDataStream dataStream(&data,QIODevice::WriteOnly);
    message.serialize(dataStream);
    socket.write(data);
}

void tcpsocket::tcpConnect(QString ipAddress)
{
    socket.connectToHost(ipAddress,1234,QIODevice::ReadWrite);
}

void tcpsocket::onConnected()
{

}

void tcpsocket::onDisConnected()
{

}

void tcpsocket::onReadyRead()
{
    QObject* obj = this->sender();
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(obj);
    QByteArray data = socket->readAll();
    QDataStream dataStream(&data,QIODevice::ReadOnly);
    Message message;
    message.deserialize(dataStream);
    emit socketReceiveMessage(message);
}

void tcpsocket::onError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError);
}
