/**
 * Created on Tue Jul 31 2021
 * 
 * Copyright (c) 2021 - Mathéo G - All Right Reserved
 * 
 * Licensed under the Apache License, Version 2.0
 * Available on GitHub at https://github.com/Paracetamol56/Observeur2 */

#include "settingdialog.h"
#include "ui_settingdialog.h"

SettingDialog::SettingDialog(QWidget *parent)
    : QDialog(parent)
    , m_ui(new Ui::SettingDialog)
{
    m_ui->setupUi(this);

    QSettings settings;

    if (settings.contains("theme") == false)
    {
        m_ui->CancelPushButton->setEnabled(false);
    }
    else
    {
        // Theme
        if (settings.value("theme").toString() == "dark")
        {
            m_ui->DarkRadioButton->setChecked(true);
            m_ui->LightRadioButton->setChecked(false);
            m_ui->RedRadioButton->setChecked(false);
        }
        else if (settings.value("theme").toString() == "light")
        {
            m_ui->DarkRadioButton->setChecked(false);
            m_ui->LightRadioButton->setChecked(true);
            m_ui->RedRadioButton->setChecked(false);
        }
        else if (settings.value("theme").toString() == "red")
        {
            m_ui->DarkRadioButton->setChecked(false);
            m_ui->LightRadioButton->setChecked(false);
            m_ui->RedRadioButton->setChecked(true);
        }

        // Database
        m_ui->DBPathLineEdit->setText(settings.value("database").toString());

        settings.beginGroup("position");
        // Longitude
        Angle latitude(settings.value("latitude").toDouble());
        m_ui->LatDegreeSpinBox->setValue(latitude.getDegree());
        m_ui->LatMinuteSpinBox->setValue(latitude.getDegreeMinute());
        m_ui->LatSecondDoubleSpinBox->setValue(latitude.getDegreeSecond());
        m_ui->LatComboBox->setCurrentText(settings.value("latitudeDirection").toString());

        // Latitude
        Angle longitude(settings.value("longitude").toDouble());
        m_ui->LonDegreeSpinBox->setValue(longitude.getDegree());
        m_ui->LonMinuteSpinBox->setValue(longitude.getDegreeMinute());
        m_ui->LonSecondDoubleSpinBox->setValue(longitude.getDegreeSecond());
        m_ui->LonComboBox->setCurrentText(settings.value("longitudeDirection").toString());

        // Altitude
        m_ui->AltitudeSpinBox->setValue(settings.value("altitude").toInt());

        settings.endGroup();

        m_ui->CancelPushButton->setEnabled(true);
    }
}


SettingDialog::~SettingDialog()
{
    delete m_ui;
}


void SettingDialog::on_SavePushButton_clicked()
{
    // Keys stored in settings :
    /*
     * "theme" ("dark", "light" or "red")
     * "database" (path)
     * group "position" :
     *      - latitude (double totalDegree)
     *      - longitude (double totalDegree)
     *      - altitude (int)
     */

    QSettings settings;

    if (m_ui->DarkRadioButton->isChecked())
    {
        QFile qssFile(":/qdarkstyle/dark/Ressources/dark/dark.qss");

        if (qssFile.exists() == false)
        {
            MissingFileError errorMessage(ErrorPriority::Critical, "Le fichier de style est introuvable", &qssFile);
            errorMessage.printMessage();
        }
        else
        {
            settings.setValue("theme", QString("dark"));
            qssFile.open(QFile::ReadOnly | QFile::Text);
            QTextStream ts(&qssFile);
            qApp->setStyleSheet(ts.readAll());
        }
    }
    else if (m_ui->LightRadioButton->isChecked())
    {
        QFile qssFile(":/qdarkstyle/light/Ressources/light/light.qss");

        if (qssFile.exists() == false)
        {
            MissingFileError errorMessage(ErrorPriority::Critical, "Le fichier de style est introuvable", &qssFile);
            errorMessage.printMessage();
        }
        else
        {
            settings.setValue("theme", QString("light"));
            qssFile.open(QFile::ReadOnly | QFile::Text);
            QTextStream ts(&qssFile);
            qApp->setStyleSheet(ts.readAll());
        }
    }
    else if (m_ui->RedRadioButton->isChecked())
    {
        QFile qssFile(":/qdarkstyle/red/Ressources/red/red.qss");

        if (qssFile.exists() == false)
        {
            MissingFileError errorMessage(ErrorPriority::Critical, "Le fichier de style est introuvable", &qssFile);
            errorMessage.printMessage();
        }
        else
        {
            settings.setValue("theme", QString("red"));
            qssFile.open(QFile::ReadOnly | QFile::Text);
            QTextStream ts(&qssFile);
            qApp->setStyleSheet(ts.readAll());
        }
    }

    settings.setValue("database", m_ui->DBPathLineEdit->text());

    Angle latitude(false, m_ui->LatDegreeSpinBox->value(), m_ui->LatMinuteSpinBox->value(), m_ui->LatSecondDoubleSpinBox->value());
    Angle longitude(false, m_ui->LonDegreeSpinBox->value(), m_ui->LonMinuteSpinBox->value(), m_ui->LonSecondDoubleSpinBox->value());

    settings.beginGroup("position");
    settings.setValue("latitude", latitude.getTotalDegree());
    settings.setValue("latitudeDirection", m_ui->LatComboBox->currentText());
    settings.setValue("longitude", longitude.getTotalDegree());
    settings.setValue("longitudeDirection", m_ui->LonComboBox->currentText());
    settings.setValue("altitude", m_ui->AltitudeSpinBox->value());
    settings.endGroup();

    close();
}


void SettingDialog::on_CancelPushButton_clicked()
{
    close();
}


void SettingDialog::on_DBBrowsePushButton_clicked()
{
    QSettings settings;

    QString defaultPath = "";
    if (settings.contains("database"))
    {
        defaultPath = settings.value("database").toString();
    }

    QString filename = QFileDialog::getOpenFileName(this, QString::fromUtf8("Chemin de la base de donnée"), defaultPath, "*.sqlite");
    m_ui->DBPathLineEdit->setText(filename);
    settings.setValue("database", filename);
}

