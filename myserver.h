#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>


class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = nullptr);

    void incomingConnection(qintptr socketDescriptor) override;

};

#endif // MYSERVER_H
