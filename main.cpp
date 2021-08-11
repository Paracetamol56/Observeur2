#include "mainwindow.h"
#include <QApplication>

#include <QFile>
#include <QDir>

#include <QLatin1String>
#include <QString>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.showMaximized();

    return app.exec();
}
