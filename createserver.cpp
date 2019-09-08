#include "createserver.h"
#include "ui_createserver.h"
#include <QMessageBox>
#include <QFont>
#include <QPalette>
#include <QPainter>

CreateServer::CreateServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateServer)
{
    ui->setupUi(this);
    ui->lineEditIP->setText("127.0.0.1");
    ui->lineEditPort->setText("8888");
}

CreateServer::~CreateServer()
{
    delete ui;
}

QHostAddress CreateServer::getHostAddress() {
    QString ip = ui->lineEditIP->text();
    if ( ip == "127.0.0.1") {
        return QHostAddress::LocalHost;
    } else if (ip == "0.0.0.0"){
        return QHostAddress::Any ;
    } else {
        return QHostAddress(ip);
    }
}

quint16 CreateServer::getHostPort() {
    return ui->lineEditPort->text().toUShort();
}

bool CreateServer::validate() {
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

void CreateServer::initServer()
{
    this->listenSocket =new QTcpServer;

    QObject::connect(this->listenSocket,SIGNAL(newConnection()),this,SLOT(acceptConnection()));

    this->listenSocket->listen(getHostAddress(),getHostPort());

    QMessageBox::information(this, "Start", "You have start a host. Please wait for client.",
                                           QMessageBox::Ok);
    ui->information->setText("waiting for client");

}

void CreateServer::acceptConnection()
{
    qDebug() << "server ac";
    waiting = true;
    this->readWriteSocket =this->listenSocket->nextPendingConnection();

    transmit() << "hello" << endl;

    waiting = false;
    ui->pushButtonOK->setEnabled(true);
    ui->pushButtonCancel->setEnabled(true);
    ui->lineEditIP->setEnabled(true);
    ui->lineEditPort->setEnabled(true);
    ui->information->setText("Connected");
    QMessageBox::information(this, "Success", "You have connected to a client. Please wait start the game.",
                             QMessageBox::Ok);
    this->hide();

    QObject::connect(this->readWriteSocket,&QTcpSocket::readyRead, [=]() {
        recvMessage();
    });

}


void CreateServer::recvMessage()
{
    qDebug() << "fuck server!!!";
    emit data_ready();
}

void CreateServer::on_pushButtonOK_clicked()
{
    if (validate()) {
        initServer();
        ui->pushButtonOK->setEnabled(false);
        ui->pushButtonCancel->setEnabled(true);
        ui->lineEditIP->setEnabled(false);
        ui->lineEditPort->setEnabled(false);
        active = true;
    }
}

void CreateServer::on_pushButtonCancel_clicked()
{
    if (active) {
        active = false;
        this->listenSocket->close();
        ui->pushButtonOK->setEnabled(true);
        ui->pushButtonCancel->setEnabled(true);
        ui->lineEditIP->setEnabled(true);
        ui->lineEditPort->setEnabled(true);
    } else {

    }

}

QTextStream& CreateServer::transmit() {
    static QTextStream t(this->readWriteSocket);
    return t;
}
