#ifndef UDPRECV_H
#define UDPRECV_H

#include <QObject>
#include <QtNetwork/QUdpSocket>

#ifndef NAVIG_DATA_LENGTH
#define NAVIG_DATA_LENGTH 60
#endif

#ifndef NAVIG_VALUE_RATIO
#define NAVIG_VALUE_RATIO 360.0/65536.0
#endif

class Udprecv : public QObject
{
    Q_OBJECT

private:
       Udprecv(QObject *parent = nullptr);
       ~Udprecv();

public:
    static Udprecv * Instance();

    int port;
    QUdpSocket *udpSocket;
    float m_heading;

public slots:
    void dataReceived();
signals:
    void headUpdate();
};
#endif // UDPRECV_H