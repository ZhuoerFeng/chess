#ifndef CREATECLIENT_H
#define CREATECLIENT_H

#include <QDialog>
#include <QtNetwork>
#include <QTextStream>

namespace Ui {
class CreateClient;
}

class CreateClient : public QDialog
{
    Q_OBJECT

public:
    explicit CreateClient(QWidget *parent = nullptr);
    ~CreateClient();

    void connectHost();
    QTextStream& transmit();

    bool active = false;
    bool waiting = false;
    bool connected = false;
    Ui::CreateClient *ui;
    QTcpSocket *readWriteSocket;


    bool validate();
    QHostAddress getHostAddress();
    quint16 getHostPort();

signals:
    void data_ready();

public slots:
    void recvMessage();


private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();


};

#endif // CREATECLIENT_H
