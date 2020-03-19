#ifndef MESSAGERECEIVER_H
#define MESSAGERECEIVER_H
#include "message.h"
#include <vector>

class MessageObserver
{
public:
    virtual void onMessageReceived(Message message) = 0;
};

class MessageHandler
{
private:
    std::vector<MessageObserver*> observers;
public:
    MessageHandler();
    void handleMessage(Message *message);
    void addObserver(MessageObserver *observer);
    void removeObserver(MessageObserver *observer);
};

#endif // MESSAGERECEIVER_H
