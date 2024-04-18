#include <fstream>

#include <QApplication>
#include <QFontDatabase>
#include <QQuickView>
#include <QQmlContext>
#include <QQmlEngine>

#include "udpmesg.hpp"

int main(int argc, char *argv[])
{
   // Q_INIT_RESOURCE(Nav);
    QApplication app(argc, argv);
    app.setOrganizationName("Marautec");
    app.setOrganizationDomain("Marautec.com");
    app.setApplicationName("Nav");

    qmlRegisterType<NavMesg>("udp.marautec.com", 23, 2, "NavMesg");

    QQuickView view;
    view.setSource(QUrl("qrc:/udp.qml"));
    //view.showMaximized();
    view.resize(1920,1080);
    view.show();
    app.exec();
    return true;
}