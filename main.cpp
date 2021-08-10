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
/*
    // Open the QSS file
    QFile qssFile(":/Ressources/lightTheme.qss");
    qssFile.open(QFile::ReadOnly);
    QString styleSheet { QLatin1String(qssFile.readAll()) };

    // Setup stylesheet
    app.setStyleSheet(styleSheet);
*/
    return app.exec();
}
