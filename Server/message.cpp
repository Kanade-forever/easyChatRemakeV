#include "message.h"

Message::Message()
{
}

Message *Message::setContent(const QByteArray &_content)
{
    this->content = _content;
    return this;
}

Message *Message::setType(messageType _type)
{
    this->type = _type;
    return this;
}

Message *Message::setTime(const QDateTime &_time)
{
    this->sendTime = _time;
    return this;
}

Message *Message::setSender(const QString &_sender)
{
    this->sender = _sender;
    return this;
}

void Message::serialize(QDataStream &stream) const
{
    int _type = type;
    stream<<sender<<sendTime<<_type<<content;
}

void Message::deserialize(QDataStream &stream)
{
    int _type;
    stream>>sender>>sendTime>>_type>>content;
    type = static_cast<messageType>(_type);
}
