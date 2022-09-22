#ifndef DATARECEIVER_H
#define DATARECEIVER_H

#include "qudpsocket.h"
#include <QMainWindow>

#include <QTcpServer>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class DataReceiver; }
QT_END_NAMESPACE

class DataReceiver : public QMainWindow
{
    Q_OBJECT

public:
    DataReceiver(QWidget *parent = nullptr);
    ~DataReceiver();

private:
    Ui::DataReceiver *ui;

    QTcpServer *tcpsunucu;
    QTcpSocket *tcpsoket;
    QUdpSocket* udpReceiver;


public slots:
    void yeniBaglanti();
    void hazir();
    void baglantiyiKapat();

    void processPendingDatagram();
};
#endif // DATARECEIVER_H






