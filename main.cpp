#include "mainwindow.h"
#include <QApplication>

#include <QFile>
#include <QDir>

#include <QLatin1String>
#include <QString>

int main(int argc, char *argv[])
{
    // Application informations
    QCoreApplication::setOrganizationName("L'Observeur2");
    QCoreApplication::setOrganizationDomain("lobserveur2.com"); // Don't try, this is fake
    QCoreApplication::setApplicationName("L'Observeur2");

    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.showMaximized();

    return app.exec();
}
