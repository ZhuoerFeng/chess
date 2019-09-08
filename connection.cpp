//#include "connection.h"
//#include "createconnectionsession.h"
//#include <QObject>
//#include <QMessageBox>

//Connection::Connection(QObject *parent) : QObject(parent)
//{

//}

//Connection* Connection::createServer() {
//    auto connection = new Connection;
//    auto dialog = new CreateServerSession;
//    connection->server = new QTcpServer;
//    connect(connection->server, &QTcpServer::newConnection, [&](){
//        connection->socket = connection->server->nextPendingConnection();
//        connection->server->disconnect(SIGNAL(newConnection())); // why?
//        connection->initialze();
//        dialog->hide();
//        delete dialog;
//        QMessageBox::information(nullptr, "Connection", "Connection Sucess! Please start the game.",
//                                 QMessageBox::Ok);
//    });

//}

//Connection* Connection::createClient() {
//    auto connection = new Connection;
//    auto dialog = new CreateClientSession;
//    connection->socket = new QTcpSocket;
////    connect(connection->socket, &QTcpSocket::)
//}

//void Connection::initialze() {
//    active = true;
//    if (isServer()) {
//        transmit() << "hello";
//    } else {

//    }
//    connect(socket, &QTcpSocket::readyRead, [&](){
//       emit readyRead();
//    });
//    emit connected();
//}


//bool Connection::isActive() {
//    return active;
//}

//bool Connection::isServer() {
//    return isActive() && server!=nullptr;
//}

//bool Connection::isClient() {
//    return isActive() && server == nullptr;
//}
