#ifndef CREATESERVER_H
#define CREATESERVER_H

#include <QDialog>
#include <QtNetwork>
#include <QTextStream>

namespace Ui {
class CreateServer;
}

class CreateServer : public QDialog
{
    Q_OBJECT

public:
    explicit CreateServer(QWidget *parent = nullptr);
    ~CreateServer();
    void initServer();
    bool waiting  = false;
    bool active = false;
    QTextStream& transmit();

    Ui::CreateServer *ui;
    QTcpServer  *listenSocket;
    QTcpSocket  *readWriteSocket;

    bool validate();
    QHostAddress getHostAddress();
    quint16 getHostPort();

signals:
    void data_ready();

public slots:
    void acceptConnection();
    void recvMessage();

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();



};

#endif // CREATESERVER_H

