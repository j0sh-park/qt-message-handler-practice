#ifndef MESSAGEPRESENDER_H
#define MESSAGEPRESENDER_H
#include <QTableView>
#include <QStringList>
#include <QString>
#include "messagehandler.h"
#include <QThread>
#include <QStack>
#include <QStringListModel>
#include <QMutex>
#include <QWaitCondition>
#include <QT>
#include <QtConcurrent>
#include <QMetaObject>
#include <QList>
#include <QVariant>

class MessageModel : public QAbstractListModel
{
    Q_OBJECT

private:
    QList<Message> *messages;
public:
    enum roles {
        IDRole = Qt::UserRole + 1,
        MessageRole
    };
    MessageModel();

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    void updateMessages(QList<Message> &messages);
};

class MessagePresenter : public QObject, public MessageObserver
{
    Q_OBJECT
private:
    QMutex sync;
    MessageHandler *handler;
    MessageModel *model;
    QStack<Message> *messageStack;
public:
    MessagePresenter(MessageHandler *handler, QTableView *tableView);
    void onMessageReceived(Message message) override;
    void displayOnBackground();
};

#endif // MESSAGEPRESENDER_H
