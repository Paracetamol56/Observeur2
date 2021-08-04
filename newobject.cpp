#include "newobject.h"
#include "ui_newobject.h"


///
/// Constructor
/// \brief NewObject::NewObject
/// \param parent
/// \param db
///
NewObject::NewObject(QWidget *parent, QSqlDatabase *db)
    : QWidget(parent)
    , m_ui(new Ui::NewObject)
    , m_db(db)
{
    // ########################## Setup the UI ######################### //

    m_ui->setupUi(this);


    // ######### Get data from database to fill the constallation table ########## //

    // Open the database connection
    m_db->open();

    // Query container object
    QSqlQuery query;

    // === Type query
    // Set the query
    query.prepare("SELECT `category_name` AS `Type` FROM `categories` WHERE 1 ORDER BY `category_name` ASC");
    query.exec();

    // Add items one by one in a list widget
    while(query.next())
    {
        QString itemStr = query.value(0).toString();
        m_ui->TypeComboBox->addItem(itemStr);
    }

    // === Constellation query
    // Set the query
    query.prepare("SELECT `constellation_name` AS `Constellations` FROM `constellations` WHERE 1 ORDER BY `constellation_name` ASC");
    query.exec();

    // Add items one by one in a list widget
    while(query.next())
    {
        QString itemStr = query.value(0).toString();
        m_ui->ConstellationComboBox->addItem(itemStr);
    }

    // Close the database connection
    m_db->close();
}


///
/// Destructor
/// \brief NewObject::~NewObject
///
NewObject::~NewObject()
{
    delete m_ui;
}


///
/// Verify all input fields and call error message in case of invalid values
/// \brief NewObject::CheckInput
/// \return true if all is right
///
bool NewObject::CheckInput()
{
    // === Name verification
    QString testName = m_ui->NameLineEdit->text();
    if (testName == "")
    {
        qDebug() << "Error : name";
        return false;
    }
    else
    {
        // Select all object with the same name
        m_db->open();
        QSqlQuery query("SELECT `objects_id` FROM `objects` WHERE `object_name` = \"" + testName + "\"");
        query.exec();
        m_db->close();
        if (query.next())
        {
            qDebug() << "Error : name exists";
            return false;
        }
        else
        {
            qDebug() << "OK : name";
            qDebug() << "Name : " << testName;
        }
    }


    // === Other name 1 verification
    QString testOtherName1 = m_ui->OtherNameLineEdit_1->text();
    if (testOtherName1 != "")
    {
        // Select all object with the same name
        m_db->open();
        QSqlQuery query("SELECT `objects_id` FROM `objects` WHERE `object_othername1` = \"" + testOtherName1 + "\"");
        query.exec();
        m_db->close();
        if (query.next())
        {
            qDebug() << "Error : othername1 exists";
            return false;
        }
        else
        {
            qDebug() << "OK : othername1";
            qDebug() << "Name : " << testOtherName1;
        }
    }


    // === Other name 2 verification
    QString testOtherName2 = m_ui->OtherNameLineEdit_2->text();
    if (testOtherName2!= "")
    {
        // Select all object with the same name
        m_db->open();
        QSqlQuery query("SELECT `objects_id` FROM `objects` WHERE `object_othername2` = \"" + testOtherName2 + "\"");
        query.exec();
        m_db->close();
        if (query.next())
        {
            qDebug() << "Error : othername2 exists";
            return false;
        }
        else
        {
            qDebug() << "OK : othername2";
            qDebug() << "Name : " << testOtherName2;
        }
    }


    // === Position verification
    // RA
    QString testRightAscention =
            QString::number(m_ui->RAHourSpinBox->value())
            + "h"
            + QString::number(m_ui->RAMinuteSpinBox->value())
            + "m"
            + QString::number(m_ui->RASecondDoubleSpinBox->value())
            + "s";
    qDebug() << "OK : RightAscention";
    qDebug() << "Name : " << testRightAscention;

    // Dec
    QString testDeclination =
            QString::number(m_ui->DecDegreeSpinBox->value())
            + "°"
            + QString::number(m_ui->DecMinuteSpinBox->value())
            + "\'"
            + QString::number(m_ui->DecSecondDoubleSpinBox->value())
            + "\"";
    qDebug() << "OK : Declination";
    qDebug() << "Name : " << testDeclination;


    // === Magnitude verification
    double testApparentMagnitude = m_ui->ApparentMagnitudeDoubleSpinBox_1->value();
    double testSecondApparentMagnitude = 0.00;
    if (m_ui->ApparentMagnitudeDoubleSpinBox_2->isEnabled())
    {
        testSecondApparentMagnitude = m_ui->ApparentMagnitudeDoubleSpinBox_2->value();
        if (testApparentMagnitude > testSecondApparentMagnitude)
        {
            // Swap variables
            testApparentMagnitude = testApparentMagnitude + testSecondApparentMagnitude;
            testSecondApparentMagnitude = testApparentMagnitude - testSecondApparentMagnitude;
            testApparentMagnitude = testApparentMagnitude - testSecondApparentMagnitude;

            // Update spinboxes
            m_ui->ApparentMagnitudeDoubleSpinBox_1->setValue(testApparentMagnitude);
            m_ui->ApparentMagnitudeDoubleSpinBox_2->setValue(testSecondApparentMagnitude);
        }
        qDebug() << "OK : SecondApparentMagnitude";
        qDebug() << "SecondApparentMagnitude : " << testSecondApparentMagnitude;
    }
    qDebug() << "OK : ApparentMagnitude";
    qDebug() << "ApparentMagnitude : " << testApparentMagnitude;


    m_name = testName;
    m_otherName1 = testOtherName1;
    m_otherName2 = testOtherName2;
    m_rightAscension = testRightAscention;
    m_declination = testDeclination;
    m_apparentMagnitude = testApparentMagnitude;
    m_secondApparentMagnitude = testSecondApparentMagnitude;

    return true;
}


///
/// When the user finish typing in OtherNameLineEdit_1,
/// check if there is text and enable (or not) OtherNameLineEdit_2
/// \brief NewObject::on_OtherNameLineEdit_1_editingFinished
///
void NewObject::on_OtherNameLineEdit_1_editingFinished()
{
    if (m_ui->OtherNameLineEdit_1->text() == "")
    {
        m_ui->OtherNameLineEdit_2->setEnabled(false);
        m_ui->OtherNameLabel->setText("Autre nom");
    }
    else
    {
        m_ui->OtherNameLineEdit_2->setEnabled(true);
        m_ui->OtherNameLabel->setText("Autres noms");
    }
}


///
/// When the user finish selection,
/// check if the choice is "Etoile double" and enable (or not) OtherNameLineEdit_2
/// \brief NewObject::on_TypeComboBox_currentTextChanged
/// \param arg1
///
void NewObject::on_TypeComboBox_currentTextChanged(const QString &arg1)
{
    if (arg1 == "Etoile double")
    {
        m_ui->ApparentMagnitudeDoubleSpinBox_2->setEnabled(true);
    }
    else
    {
        m_ui->ApparentMagnitudeDoubleSpinBox_2->setEnabled(false);
    }
}


///
/// When The note value is changed on the slider
/// \brief NewObject::on_NoteHorizontalSlider_valueChanged
/// \param value
///
void NewObject::on_NoteHorizontalSlider_valueChanged(int value)
{
    m_ui->NoteDisplayLabel->setText(QString(QString::number(value) + "/10"));
    m_note = value;
}


///
/// When the cancel button is clicked
/// \brief NewObject::on_CancelPushButton_clicked
///
void NewObject::on_CancelPushButton_clicked()
{
    close();
}


///
/// Save Button
/// \brief NewObject::on_SavePushButton_clicked
///
void NewObject::on_SavePushButton_clicked()
{
    qDebug() << CheckInput();
}
