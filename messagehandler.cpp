#include "messagehandler.h"

MessageHandler::MessageHandler()
{

}

void MessageHandler::handleMessage(Message *message)
{
    for (MessageObserver *observer : observers)
    {
        observer->onMessageReceived(Message(*message));
    }
}

void MessageHandler::addObserver(MessageObserver *observer)
{
    observers.push_back(observer);
}

void MessageHandler::removeObserver(MessageObserver *observer)
{
    for (std::vector<MessageObserver*>::iterator to_remove = observers.begin(); to_remove != observers.end(); to_remove++)
    {
        if (*to_remove == observer)
        {
            observers.erase(to_remove);
            break;
        }
    }
}
