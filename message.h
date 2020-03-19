#ifndef MESSAGE_H
#define MESSAGE_H
#include <QString>

class Message
{
public:
    int id;
    QString message;
public:
    Message();
    Message(int id);
    Message(const Message &from);
};

#endif // MESSAGE_H
