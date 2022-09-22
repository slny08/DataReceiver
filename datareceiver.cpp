#include "datareceiver.h"
#include "ui_datareceiver.h"

#include<QtNetwork>

DataReceiver::DataReceiver(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DataReceiver)
{
    ui->setupUi(this);
    tcpsunucu = new QTcpServer;
    connect(tcpsunucu,SIGNAL(newConnection()),this,SLOT(yeniBaglanti()));

    if(tcpsunucu -> listen(QHostAddress::LocalHost,1234)){
        qDebug() << "sunucu baslatildi";
    }
    else{
        qDebug() << "sunucu baslatilamadi";
    }

    udpReceiver=new QUdpSocket(this);
    udpReceiver->bind(2323,QUdpSocket::ShareAddress);

    connect(udpReceiver,&QUdpSocket::readyRead,this,&DataReceiver::processPendingDatagram);

}

DataReceiver::~DataReceiver()
{
    delete ui;
}

void DataReceiver::yeniBaglanti()
{
        tcpsoket = tcpsunucu->nextPendingConnection();
        tcpsoket ->waitForBytesWritten();

        connect(tcpsoket,SIGNAL(readyRead()),SLOT(hazir()));
        connect(tcpsoket,SIGNAL(disconnected()),SLOT(baglantiyiKapat()));

}

void DataReceiver::hazir()
{
QByteArray veri = tcpsoket->readAll();
ui->textBrowser->setText(veri);
ui->textBrowser->setStyleSheet("background-color: green");
 QTimer::singleShot(10000,this,[=]{ui->textBrowser->setStyleSheet("background-color:white");});
}

void DataReceiver::baglantiyiKapat()
{
    qDebug() << "Baglanti sonlandi";
}

void DataReceiver::processPendingDatagram()
{
    while(udpReceiver->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpReceiver->pendingDatagramSize());
        udpReceiver->readDatagram(datagram.data(),datagram.size());
        ui->textBrowser->setText(QString::fromLocal8Bit(  datagram));
        ui->textBrowser->setStyleSheet("background-color: green");
         QTimer::singleShot(10000,this,[=]{ui->textBrowser->setStyleSheet("background-color:white");});
        }
    }


