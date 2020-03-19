#ifndef MESSAGESENDTESTER_H
#define MESSAGESENDTESTER_H

#include "messagehandler.h"
#include <QtConcurrent>

class MessageSendTester
{
private:
    MessageHandler *handler;
    void sendTestMessages(int count);
public:
    MessageSendTester(MessageHandler *handler);
    void startTest(int count);
};

#endif // MESSAGESENDTESTER_H
