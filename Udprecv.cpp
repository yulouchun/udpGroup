
#include "Udprecv.hpp"
#include <iostream>
#include <QTimer>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QNetworkDatagram>
#include <QtNetwork/QNetworkInterface>

Udprecv * Udprecv::Instance()
{
    static Udprecv udprecv;
    return &udprecv;
}

Udprecv::Udprecv(QObject *parent)
    : QObject(parent)
{
    const QList<QNetworkInterface> &lni = QNetworkInterface::allInterfaces();
    for (int i = 0; i < lni.size();i++)
    {
        std::cout << lni[i].name().toStdString() << std::endl;
    }


    QHostAddress groupAddr = QHostAddress("224.100.100.4");
    quint16 groupPort = 23230;
    udpSocket = new QUdpSocket(this);
    udpSocket->setSocketOption(QAbstractSocket::MulticastTtlOption,1);
    bool result = udpSocket->bind(QHostAddress::AnyIPv4,groupPort,QUdpSocket::ShareAddress);
    int nIndex = 1;
    if (result == true) //bind success
    {
        udpSocket->setMulticastInterface(lni[nIndex]);
        udpSocket->joinMulticastGroup(groupAddr, lni[nIndex]);

        std::cout << "---------------------------------\n"
                  << "------udpSocket bind ok  --------\n"
                  << "---------------------------------\n";
    }
    else // bind failure
    {
        std::cout << "---------------------------------\n"
                  << "------udpSocket bind failure  --------\n"
                  << "---------------------------------\n";
        return;
    }

    
    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(dataReceived()));

    // setbuf(stdout, NULL);
}

void Udprecv::dataReceived()
{
    std::cout << "======= dataReceived===================" << std::endl;
    while(udpSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());

        std::cout << "recv datagram size  = " << datagram.size() << std::endl;

        if(datagram.size() == NAVIG_DATA_LENGTH) //length
        {
            unsigned int H = *(datagram.data() + 22);
            unsigned int L = *(datagram.data() + 23);
            unsigned value = (H << 8) | L;
            m_heading = value * 360.0f/65536.0f; // * NAVIG_VALUE_RATIO;
            printf("%02X %02X\n",H,L);
            emit headUpdate();

            qDebug() << "m_heading:" << m_heading;
        }
    }
     std::cout << "====================================" << std::endl;
}


Udprecv::~Udprecv()
{
    udpSocket->close();
}
