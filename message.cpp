#include "message.h"
#include <string>


Message::Message() : Message(0)
{
}

Message::Message(int id)
{
    this->id = id;
    this->message = QString::fromStdString("Message " + std::to_string(this->id));
}

Message::Message(const Message &from) : Message(from.id)
{
}
