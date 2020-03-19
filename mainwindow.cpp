#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "messagesendtester.h"
#include "messagepresenter.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MessageHandler *messageHandler = new MessageHandler;
    MessageSendTester *messageTester = new MessageSendTester(messageHandler);
    MessagePresenter *messagePresenter = new MessagePresenter(messageHandler, ui->tableView);
    (void)messagePresenter;

    messageTester->startTest(100000000);
}

MainWindow::~MainWindow()
{
    delete ui;
}
