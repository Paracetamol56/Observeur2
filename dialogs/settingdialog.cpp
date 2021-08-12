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
        if (settings.value("theme").toString() == "dark")
        {
            m_ui->DarkRadioButton->setChecked(true);
            m_ui->LightRadioButton->setChecked(false);
        }
        else if (settings.value("theme").toString() == "light")
        {
            m_ui->DarkRadioButton->setChecked(false);
            m_ui->LightRadioButton->setChecked(true);
        }

        settings.beginGroup("position");
        // Longitude
        Angle latitude(settings.value("latitude").toDouble());
        m_ui->LatDegreeSpinBox->setValue(latitude.getDegree());
        m_ui->LatMinuteSpinBox->setValue(latitude.getDegreeMinute());
        m_ui->LatSecondDoubleSpinBox->setValue(latitude.getDegreeSecond());
        m_ui->LatComboBox->setCurrentText(settings.value("latitudeDirection").toString());

        // Latitude
        Angle longitude(settings.value("longitude").toDouble());
        m_ui->LonDegreeSpinBox->setValue(latitude.getDegree());
        m_ui->LonMinuteSpinBox->setValue(latitude.getDegreeMinute());
        m_ui->LonSecondDoubleSpinBox->setValue(latitude.getDegreeSecond());
        m_ui->LonComboBox->setCurrentText(settings.value("longitudeDirection").toString());

        // Altitude
        m_ui->AltitudeSpinBox->setValue(settings.value("altitude").toInt());
        settings.endGroup();
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
     * "theme" ("dark" or "light")
     * group "position" :
     *      - latitude (double totalDegree)
     *      - longitude (double totalDegree)
     *      - altitude (int)
     */

    QSettings settings;

    if (m_ui->DarkRadioButton->isChecked())
    {
        QFile qssFile(":/qdarkstyle/light/Ressources/dark/dark.qss");

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
