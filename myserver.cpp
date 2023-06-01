#include "myserver.h"

MyServer::MyServer(QObject *parent)
    : QTcpServer{parent}
{

}

void MyServer::incomingConnection(qintptr socketDescriptor)
{
   QTcpSocket *socket = new QTcpSocket(this);
   socket->setSocketDescriptor(socketDescriptor);

   QObject::connect(socket, &QTcpSocket::readyRead, [&]()
   {
   QByteArray requestData = socket->readAll();
   // Traitement des données reçues

   // Exemple de réponse au client
   QByteArray responseData = "Réponse du serveur";
   socket->write(responseData);
   socket->flush();
   socket->waitForBytesWritten();
   socket->close();
   });

   QObject::connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

}
