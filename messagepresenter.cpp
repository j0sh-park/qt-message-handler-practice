#include "messagepresenter.h"
#include <iostream>
#include <algorithm>

MessagePresenter::MessagePresenter(MessageHandler *handler, QTableView *tableView)
{
    this->handler = handler;
    this->handler->addObserver(this);
    this->messageStack = new QStack<Message>();

    this->model = new MessageModel;
    tableView->setModel(model);
    tableView->setColumnWidth(0, 100);
    tableView->setColumnWidth(1, 300);

    QtConcurrent::run(this, &MessagePresenter::displayOnBackground);
}

void MessagePresenter::onMessageReceived(Message message)
{
    this->sync.lock();
    this->messageStack->push(message);
    this->sync.unlock();
}

void MessagePresenter::displayOnBackground()
{
    QList<Message> lastMessages;
    while(true) {
        if (this->messageStack->empty()) {
            continue;
        }
        QList<Message> messages;
        this->sync.lock();
        while(!this->messageStack->isEmpty() && messages.count() < 10000) {
            messages.append(this->messageStack->pop());
        }
        messageStack->clear();
        this->sync.unlock();
        for (int i = 0; i < lastMessages.count() && messages.count() < 10000; i++) {
            messages.append(lastMessages.at(i));
        }
        lastMessages.clear();
        for (int i = 0; i < messages.count(); i++) {
            lastMessages.append(messages.at(i));
        }
        this->model->updateMessages(messages);
        QThread::msleep(100);
    }
}

MessageModel::MessageModel()
{
    this->messages = new QList<Message>();
}

int MessageModel::columnCount(const QModelIndex & columnCount) const
{
    (void)columnCount;
    return 2;
}

QVariant MessageModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return "ID";
            case 1:
                return "Message";
            }
        }
    }
    return QVariant();
}

int MessageModel::rowCount(const QModelIndex & parent) const
{
    (void)parent;
    return this->messages->count();
}

QVariant MessageModel::data(const QModelIndex & index, int role) const
{
    if (index.row() < 0 || index.row() >= this->messages->count()) {
        return QVariant();
    } else if (role == Qt::TextAlignmentRole) {
        return Qt::AlignCenter;
    } else if (role == Qt::DisplayRole) {
        const Message message = this->messages->at(index.row());
        switch (index.column())
        {
        case 0:
            return message.id;
        case 1:
            return message.message;
        }
    }

    return QVariant();
}

QHash<int, QByteArray> MessageModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IDRole] = "id";
    roles[MessageRole] = "message";
    return roles;
}

void MessageModel::updateMessages(QList<Message> &messages)
{
    QModelIndex parent;
    if (messages.count() > 0) {
        beginInsertRows(parent, 0, messages.count() - 1);
        for (int i = 0; i < messages.count(); i++) {
            this->messages->insert(i, messages.at(i));
        }
        endInsertRows();
    }
    if (this->messages->count() > messages.count()) {
        beginRemoveRows(parent, messages.count(), this->messages->count() - 1);
        while(this->messages->count() > messages.count()) {
            this->messages->removeLast();
        }
        endRemoveRows();
    }
}
