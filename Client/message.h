#ifndef MESSAGE_H
#define MESSAGE_H

#include <QByteArray>
#include <QString>
#include <QDateTime>
#include <QDataStream>
#include <QMetaEnum>

class Message
{
public:
    Message();
    enum messageType{
        txt,
        img
    };

    Message* setContent(const QByteArray& _content);
    Message* setType(messageType _type);
    Message* setTime(const QDateTime& _time);
    Message* setSender(const QString& _sender);

    QByteArray getContent(){return this->content;}
    QDateTime getTime(){return this->sendTime;}
    QString getSender(){return this->sender;}
    messageType gettype(){return this->type;}

    void serialize(QDataStream &stream) const;
    void deserialize(QDataStream &stream);

private:
    QString sender;
    QDateTime sendTime;
    messageType type;
    QByteArray content;
};

#endif // MESSAGE_H
