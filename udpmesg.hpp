
#include <QObject>
#include <QtCore/qobject.h>
#include "Udprecv.hpp"

class NavMesg: public  QObject
    {
        Q_OBJECT
        Q_PROPERTY (float heading READ getHeading NOTIFY headingChanged);

        public:
            NavMesg():m_heading(0)
            {
                m_udprecv = Udprecv::Instance();
                connect(m_udprecv,SIGNAL(headUpdate()),this,SLOT(updateHead()));
            }

            float getHeading()
            {
                return m_heading;
            }
        public:
            Udprecv *m_udprecv;
            float m_heading;

        public slots:
            void updateHead(){
                m_heading = Udprecv::Instance()->m_heading;
                emit headingChanged();
                //qDebug() << "Nav msg:" << m_heading ;
            }

        signals:
            void headingChanged();  
    };