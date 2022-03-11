/**
 * Created on Tue Jul 31 2021
 * 
 * Copyright (c) 2021 - Mathéo G - All Right Reserved
 * 
 * Licensed under the Apache License, Version 2.0
 * Available on GitHub at https://github.com/Paracetamol56/Observeur2 */

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
