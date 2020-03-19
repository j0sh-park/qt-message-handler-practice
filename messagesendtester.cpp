#include "messagesendtester.h"
#include "message.h"
#include <iostream>

MessageSendTester::MessageSendTester(MessageHandler *handler)
{
    this->handler = handler;
}

void MessageSendTester::startTest(int count)
{
    QtConcurrent::run(this, &MessageSendTester::sendTestMessages, count);
}

void MessageSendTester::sendTestMessages(int count)
{
    for (int i = 0; i < count; i++) {
        Message message(i);
        this->handler->handleMessage(message);
        QThread::msleep(1);
        if (i % 1000000 == 0)
            std::cout<<i/1000000<<std::endl;
    }
    std::cout<<"sendTestMessages done."<<std::endl;
}
