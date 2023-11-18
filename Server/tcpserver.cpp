#include "tcpserver.h"

tcpserver::tcpserver(QObject *parent) : QObject(parent)
{

}

void tcpserver::runTcpServer()
{
    connect(&server,&QTcpServer::newConnection,
            this,&tcpserver::onNewConnection);

    if(server.listen(QHostAddress::AnyIPv4,1234)){
        emit this->tcpServerStatusUpdate("Listen to port:1234");
    }
}

void tcpserver::tcpServerSendMessage(Message &message)
{
    QByteArray data;
    QDataStream dataStream(&data,QIODevice::WriteOnly);
    message.serialize(dataStream);
    for(QList<QTcpSocket*>::iterator itr = sockets.begin();itr != sockets.end();itr++){
        QTcpSocket* socket = *itr;
        socket->write(data);//激活socket的ReadyRead信号
    }

}

void tcpserver::onNewConnection()
{
    emit this->tcpServerStatusUpdate("A new Client Connected");
    QTcpSocket* socket = this->server.nextPendingConnection();
    this->sockets.append(socket);

    connect(socket,&QTcpSocket::connected,
            this,&tcpserver::onConnected);
    connect(socket,&QTcpSocket::disconnected,
            this,&tcpserver::onDisConnected);
    connect(socket,&QTcpSocket::readyRead,
            this,&tcpserver::onReadyRead);
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(onError(QAbstractSocket::SocketError)));
}

void tcpserver::onConnected()
{
    QString status = "Client is connected";
    emit this->tcpServerStatusUpdate(status);
}

void tcpserver::onDisConnected()
{
    QString status = "Client is disconnected";
    emit this->tcpServerStatusUpdate(status);
}

//数据传输成功，触发ReadyRead信号
void tcpserver::onReadyRead()
{
/*
 * 获取信号发送者的方式：使用QObject::sender()
 * 该函数返回值为QObject*
 * 需要使用Qt类型转换qobject_cast<QTcpSocket*>(obj)类似c++中的dynamic_cast
*/
    QObject* obj = this->sender();
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(obj);
    QByteArray data = socket->readAll();
    Message message;
    QDataStream dataStream(&data,QIODevice::ReadOnly);
    message.deserialize(dataStream);
    emit tcpserver::tcpServerReceiveMessage(message);
}

void tcpserver::onError(QAbstractSocket::SocketError socketError)
{
    QMetaEnum metaEnum;
    QString error = metaEnum.valueToKey(socketError);
    emit this->tcpServerStatusUpdate(error);
}
