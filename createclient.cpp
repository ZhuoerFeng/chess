#include "createclient.h"
#include "ui_createclient.h"
#include <QMessageBox>

CreateClient::CreateClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateClient)
{
    ui->setupUi(this);
    ui->lineEditPort->setText("8888");
}

CreateClient::~CreateClient()
{
    delete ui;
}

QHostAddress CreateClient::getHostAddress() {
    QString ip = ui->lineEditIP->text();
    if ( ip == "127.0.0.1") {
        return QHostAddress::LocalHost;
    } else if (ip == "0.0.0.0"){
        return QHostAddress::Any ;
    } else {
        return QHostAddress(ip);
    }
}

quint16 CreateClient::getHostPort() {
    return ui->lineEditPort->text().toUShort();
}

void CreateClient::connectHost()
{
    qDebug() << "connect to host";
    this->readWriteSocket = new QTcpSocket;
    waiting = true;
    ui->information->setText("Waiting to connect.");


    QObject::connect(this->readWriteSocket,&QTcpSocket::readyRead, [=]() {
//        transmit() << "hello";
        waiting = false;
        ui->information->setText("Connected");
//        this->readWriteSocket->disconnect(SIGNAL(readyRead()));

        if (!connected) {
            QMessageBox::information(this, "Success", "You have connected to a host. Please wait for the game start.",
                                     QMessageBox::Ok);
        }
        connected = true;

        this->hide();
        recvMessage();
    });


    this->readWriteSocket->connectToHost(getHostAddress(), getHostPort());

    QMessageBox::information(this, "Connect", "ready for connection", QMessageBox::Ok);

}

void CreateClient::recvMessage()
{
    qDebug() << "fuck client!!!!";
   emit data_ready();
}


void CreateClient::on_pushButtonOK_clicked()
{
    if (validate()) {
        connectHost();
        ui->pushButtonOK->setEnabled(false);
        ui->pushButtonCancel->setEnabled(true);
        ui->lineEditIP->setEnabled(false);
        ui->lineEditPort->setEnabled(false);
        active = true;
    }
}

bool CreateClient::validate() {
    bool validated = true;
    QPalette p;
    p.setColor(QPalette::Foreground, Qt::red);

    auto serverIp = ui->lineEditIP->text();
    auto serverPort = ui->lineEditPort->text();
    auto IpPart = serverIp.split('.');
    if (IpPart.length() != 4) {
        ui->information->setPalette(p);
        ui->information->setText("Host IP not IPv4 form");
        validated = false;
    } else {
        for (int i = 0; i < 4; ++i) {
            auto part = IpPart[i];
            if (!QRegExp("\\d+").exactMatch(part)) {
                ui->information->setPalette(p);
                ui->information->setText("Host IP not IPv4 form");
                validated = false;
            }
            auto segmentVal = part.toInt();
            if (segmentVal < 0 || segmentVal > 255) {
                ui->information->setPalette(p);
                ui->information->setText("Host IP not IPv4 form");
                validated = false;
            }
        }
    }

    if (!QRegExp("\\d+").exactMatch(serverPort)) {
        ui->information->setPalette(p);
        ui->information->setText("Host Port not between 0 and 65535");
        validated = false;
    }
    auto portnum = serverPort.toInt();
    if (portnum < 0 || portnum > 65535) {
        ui->information->setPalette(p);
        ui->information->setText("Host Port not between 0 and 65535");
        validated = false;
    }
    return validated;
}

void CreateClient::on_pushButtonCancel_clicked()
{
    if (active) {
        active = false;
        ui->pushButtonOK->setEnabled(true);
        ui->pushButtonCancel->setEnabled(true);
        ui->lineEditIP->setEnabled(true);
        ui->lineEditPort->setEnabled(true);
    } else {

    }
}

QTextStream& CreateClient::transmit() {
    static QTextStream t(this->readWriteSocket);
    return t;
}
