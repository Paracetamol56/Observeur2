#include "objectform.h"
#include "ui_objectform.h"


///
/// Constructor
/// \brief ObjectForm::ObjectForm
/// \param parent
/// \param db
///
ObjectForm::ObjectForm(QWidget *parent, QSqlDatabase *db, int objectId)
    : QWidget(parent)
    , m_ui(new Ui::ObjectForm)
    , m_db(db)
    , m_objectId(objectId)
{
    // ########################## Setup the UI ######################### //

    m_ui->setupUi(this);

    // Open the database connection
    m_db->open();

    // ######### Get data from database to fill the comboboxes ######### //

    // Query container object
    QSqlQuery query;

    // === Type query
    // Set the query
    query.prepare("SELECT `category_name` AS `Type` FROM `categories` WHERE 1 ORDER BY `category_name` ASC");

    if (query.exec() == false)
    {
        Error sqlError(ErrorPriority::Warning, &query);
        sqlError.printMessage();
    }

    // Add items one by one in a list widget
    while(query.next())
    {
        QString itemStr = query.value(0).toString();
        m_ui->TypeComboBox->addItem(itemStr);
    }

    // === Constellation query
    // Set the query
    query.prepare("SELECT `constellation_name` AS `Constellations` FROM `constellations` WHERE 1 ORDER BY `constellation_name` ASC");

    if (query.exec() == false)
    {
        Error sqlError(ErrorPriority::Warning, &query);
        sqlError.printMessage();
    }

    // Add items one by one in a list widget
    while(query.next())
    {
        QString itemStr = query.value(0).toString();
        m_ui->ConstellationComboBox->addItem(itemStr);
    }

    // ################ Get the object row from the id ################# //

    if (m_objectId != 0)
    {
        // Set the window title
        setWindowTitle("Modifier un objet");

        // Set the query
        query.prepare(
                    "SELECT "
                    "objects.`object_name`, "
                    "objects.`object_messier`, "
                    "objects.`object_ngc`, "
                    "objects.`object_othername1`, "
                    "objects.`object_othername2`, "
                    "objects.`object_category`"
                    "categories.`category_name`, "
                    "objects.`object_constellation`"
                    "constellations.`constellation_name`, "
                    "objects.`object_apparent_magnitude`, "
                    "objects.`object_secondary_magnitude`, "
                    "objects.`object_distance`, "
                    "objects.`object_diameter`, "
                    "objects.`object_right_ascension`, "
                    "objects.`object_declination`, "
                    "skymap1.`skymap1_number`, "
                    "skymap2.`skymap2_number`, "
                    "skymap3.`skymap3_number`, "
                    "objects.`object_appreciation`, "
                    "objects.`object_note` "
                    "FROM objects "
                    "INNER JOIN categories "
                    "ON categories.`category_id` = objects.`object_category` "
                    "INNER JOIN constellations "
                    "ON constellations.`constellation_id` = objects.`object_constellation` "
                    "INNER JOIN skymap1 "
                    "ON skymap1.`skymap1_id` = objects.`object_skymap1_id` "
                    "INNER JOIN skymap2 "
                    "ON skymap2.`skymap2_id` = objects.`object_skymap2_id` "
                    "INNER JOIN skymap3 "
                    "ON skymap3.`skymap3_id` = objects.`object_skymap3_id` "
                    "WHERE objects.`object_id` = \"" + QString::number(m_objectId) + "\";"
                    );

        if (query.exec() == false)
        {
            Error sqlError(ErrorPriority::Warning, &query);
            sqlError.printMessage();
        }

        // Get values from query and update the form

        query.first();

        // === General section
        // Name
        m_name = query.value(0).toString();
        m_ui->NameLineEdit->setText(m_name);
        // Messier
        m_messier = query.value(1).toInt();
        m_ui->MessierSpinBox->setValue(m_messier);
        // NGC
        m_ngc = query.value(2).toInt();
        m_ui->NgcSpinBox->setValue(m_ngc);
        // Other name (1)
        m_otherName1 = query.value(3).toString();
        m_ui->OtherNameLineEdit_1->setText(m_otherName1);
        // Other name (2)
        m_otherName2 = query.value(4).toString();
        if (m_otherName2 != "")
        {
            m_ui->OtherNameLineEdit_2->setEnabled(true);
            m_ui->OtherNameLineEdit_2->setText(m_otherName2);
        }
        // Category
        m_category = query.value(5).toInt();
        m_ui->TypeComboBox->setCurrentText(query.value(6).toString());
        // Constellation
        m_constellation = query.value(7).toInt();
        m_ui->ConstellationComboBox->setCurrentText(query.value(8).toString());
        // Apparent magnitude
        m_apparentMagnitude = query.value(9).toDouble();
        m_ui->ApparentMagnitudeDoubleSpinBox_1->setValue(m_apparentMagnitude);
        // Secondary apparent magnitude
        m_secondApparentMagnitude = query.value(10).toDouble();
        if (m_secondApparentMagnitude != 0)
        {
            m_ui->ApparentMagnitudeDoubleSpinBox_2->setEnabled(true);
            m_ui->ApparentMagnitudeDoubleSpinBox_2->setValue(m_secondApparentMagnitude);
        }
        // Distance
        m_distance = query.value(11).toDouble();
        m_ui->DistanceDoubleSpinBox->setValue(m_distance);
        // Diameter
        m_diameter = query.value(12).toDouble();
        m_ui->DiametreDoubleSpinBox->setValue(m_diameter);

        // === Position section
        // Right ascension
        m_rightAscension = query.value(13).toString();
        {
            int hour = m_rightAscension.split('h').front().toInt();
            int minute = m_rightAscension.split('h').back().split('m').front().toInt();
            double second = m_rightAscension.split('m').back().split('s').front().toDouble();
            m_ui->RAHourSpinBox->setValue(hour);
            m_ui->RAMinuteSpinBox->setValue(minute);
            m_ui->RASecondDoubleSpinBox->setValue(second);
        }
        // Declination
        m_declination = query.value(14).toString();
        {
            int degreeIndex = m_declination.indexOf("°");
            int minuteIndex = m_declination.indexOf("'");
            int secondIndex = m_declination.indexOf(QChar('\"'));

            QString StrData = m_declination;
            QString HexStrData;
            for (int i = 0; i < StrData.length(); i++) {
                HexStrData.append(QString::number(StrData.at(i).unicode(), 10));
                HexStrData.append(" ");
            }

            qDebug() << HexStrData;

            qDebug() << (char)39 << m_declination.count((char)39);

            qDebug() << degreeIndex;
            qDebug() << minuteIndex;
            qDebug() << secondIndex;

            qDebug() << m_declination.mid(0, degreeIndex);
            qDebug() << m_declination.mid(degreeIndex, minuteIndex);
            qDebug() << m_declination.mid(minuteIndex, secondIndex);

            int degree = m_declination.split("°").front().toInt();
            int minute = m_declination.split("°").back().split("\'").front().toInt();
            double second = m_declination.split("\'").back().split("\"").front().toDouble();
            m_ui->DecDegreeSpinBox->setValue(degree);
            m_ui->DecMinuteSpinBox->setValue(minute);
            m_ui->DecSecondDoubleSpinBox->setValue(second);
        }

        // === Skymap section
        // Skymap 1
        m_skyMap1 = query.value(15).toInt();
        m_ui->Map1SpinBox->setValue(m_skyMap1);
        // Skymap 2
        m_skyMap2 = query.value(16).toInt();
        m_ui->Map2SpinBox->setValue(m_skyMap2);
        // Skymap 3
        m_skyMap3 = query.value(17).toInt();
        m_ui->Map3SpinBox->setValue(m_skyMap3);

        // === Appreciation section
        m_description = query.value(18).toString();
        m_ui->DescriptionTextEdit->setText(m_description);
        m_note = query.value(19).toInt();
        m_ui->NoteDisplayLabel->setText(QString::number(m_note));
        m_ui->NoteHorizontalSlider->setValue(m_note);
    }
    else
    {
        query.prepare("SELECT MAX(object_id) FROM objects");

        if (query.exec() == false)
        {
            Error sqlError(ErrorPriority::Warning, &query);
            sqlError.printMessage();
        }

        query.first();
        m_objectId = query.value(0).toInt() + 1;
    }

    // Close the database connection
    m_db->close();
}


///
/// Destructor
/// \brief NewObject::~NewObject
///
ObjectForm::~ObjectForm()
{
    delete m_ui;
}


///
/// Verify all input fields and call error message in case of invalid values
/// \brief NewObject::CheckInput
/// \return true if all is right
///
bool ObjectForm::CheckInput()
{
    // === Name verification
    QString testName = m_ui->NameLineEdit->text();
    if (testName == "")
    {
        throw Error(ErrorPriority::BadInput, ErrorType::MissingInput, "Vous devez specifier un nom");
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
            throw Error(ErrorPriority::BadInput, ErrorType::InvalidInput, "Ce nom existe déjà dans la base de donnée");
            return false;
        }
        else
        {
            qDebug() << "OK : name";
            qDebug() << "Name : " << testName;
        }
    }


    // === Messier verification
    int testMessier = m_ui->MessierSpinBox->value();
    if (testMessier != 0)
    {
        // Select all object with the same name
        m_db->open();
        QSqlQuery query("SELECT `objects_id` FROM `objects` WHERE `object_messier` = \"" + QString::number(testMessier) + "\"");
        query.exec();
        m_db->close();
        if (query.next())
        {
            throw Error(ErrorPriority::BadInput, ErrorType::InvalidInput, "Cet object messier existe déjà dans la base de donnée");
            return false;
        }
        else
        {
            qDebug() << "OK : messier";
            qDebug() << "Messier : " << testMessier;
        }
    }


    // === NGC verification
    int testNgc = m_ui->NgcSpinBox->value();
    if (testNgc != 0)
    {
        // Select all object with the same name
        m_db->open();
        QSqlQuery query("SELECT `objects_id` FROM `objects` WHERE `object_ngc` = \"" + QString::number(testNgc) + "\"");
        query.exec();
        m_db->close();
        if (query.next())
        {
            throw Error(ErrorPriority::BadInput, ErrorType::InvalidInput, "Cet object NGC existe déjà dans la base de donnée");
            return false;
        }
        else
        {
            qDebug() << "OK : NGC";
            qDebug() << "NGC : " << testMessier;
        }
    }


    // === Other name 1 verification
    QString testOtherName1 = m_ui->OtherNameLineEdit_1->text();
    if (testOtherName1 != "")
    {
        // Select all object with the same name
        m_db->open();
        QSqlQuery query("SELECT `objects_id` FROM `objects` WHERE `object_othername1` = \"" + testOtherName1 + "\" OR `object_othername2` = \"" + testOtherName1 + "\"");
        query.exec();
        m_db->close();
        if (query.next())
        {
            throw Error(ErrorPriority::BadInput, ErrorType::InvalidInput, "Cet autre nom (1) existe déjà dans la base de donnée");
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
        QSqlQuery query("SELECT `objects_id` FROM `objects` WHERE `object_othername1` = \"" + testOtherName2 + "\" OR `object_othername2` = \"" + testOtherName2 + "\"");
        query.exec();
        m_db->close();
        if (query.next())
        {
            throw Error(ErrorPriority::BadInput, ErrorType::InvalidInput, "Cet autre nom (2) existe déjà dans la base de donnée");
            return false;
        }
        else
        {
            qDebug() << "OK : othername2";
            qDebug() << "Name : " << testOtherName2;
        }
    }

    // === Type verification
    // Select type id with the same type name
    int testType = 0;
    {
        m_db->open();
        QSqlQuery query("SELECT `category_id` "
                        "FROM `categories` "
                        "WHERE `category_name` = \"" + m_ui->TypeComboBox->currentText() + "\"");
        if (query.exec() == false)
        {
            Error sqlError(ErrorPriority::Warning, &query);
            sqlError.printMessage();
        }
        m_db->close();
        if (query.next())
        {
            testType = query.value(0).toInt();
            qDebug() << "OK : Types";
            qDebug() << "Name : " << testType;
        }
    }


    // === Constellation verification
    // Select constellation id with the same constellation name
    int testConstellation = 0;
    {
        m_db->open();
        QSqlQuery query("SELECT `constellation_id` "
                        "FROM `constellations` "
                        "WHERE `constellation_name` = \"" + m_ui->ConstellationComboBox->currentText() + "\"");
        if (query.exec() == false)
        {
            Error sqlError(ErrorPriority::Warning, &query);
            sqlError.printMessage();
        }
        m_db->close();
        if (query.next())
        {
            testConstellation = query.value(0).toInt();
            qDebug() << "OK : Constellation";
            qDebug() << "Name : " << testConstellation;
        }
    }


    // === Magnitude verification
    double testApparentMagnitude = m_ui->ApparentMagnitudeDoubleSpinBox_1->value();
    double testSecondApparentMagnitude = 0;
    if (m_ui->ApparentMagnitudeDoubleSpinBox_2->isEnabled())
    {
        testSecondApparentMagnitude = m_ui->ApparentMagnitudeDoubleSpinBox_2->value();
        // If primary magnitude > secondary magnitude : swap variables
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
    else
    {
        testSecondApparentMagnitude = 0;
    }
    qDebug() << "OK : ApparentMagnitude";
    qDebug() << "ApparentMagnitude : " << testApparentMagnitude;


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
            + "\'\'";
    qDebug() << "OK : Declination";
    qDebug() << "Name : " << testDeclination;


    // COPYING TEST VALUES INTO ATTRIBUTES

    // === General section
    // Common name
    m_name = testName;
    // Messier
    m_messier = testMessier; // <<-- "" if undefined
    // NGC
    m_ngc = testNgc; // <<-- "" if undefined
    // Othernames
    m_otherName1 = testOtherName1; // <<-- NULL if undefined
    m_otherName2 = testOtherName2; // <<-- NULL if undefined
    // Type
    m_category = testType;
    // Constellation
    m_constellation = testConstellation;
    // Apperent magnitude (primary)
    m_apparentMagnitude = testApparentMagnitude;
    // Apperent magnitude (secondary)
    m_secondApparentMagnitude = testSecondApparentMagnitude; // <<-- NULL if undefined
    // Diameter
    m_diameter = m_ui->DiametreDoubleSpinBox->value();
    // Distance
    m_distance = m_ui->DistanceDoubleSpinBox->value();

    // === Position section
    // Right ascension
    m_rightAscension = testRightAscention;
    // Declination
    m_declination = testDeclination;

    // === Skymap section
    // Map 1
    m_skyMap1 = m_ui->Map1SpinBox->value();
    // Map 2
    m_skyMap2 = m_ui->Map1SpinBox->value();
    // Map 3
    m_skyMap3 = m_ui->Map1SpinBox->value();

    // === Appreciation section
    // Description
    m_description = m_ui->DescriptionTextEdit->toPlainText();
    m_note = m_ui->NoteHorizontalSlider->value();


    return true;
}


///
/// When the user finish typing in OtherNameLineEdit_1,
/// check if there is text and enable (or not) OtherNameLineEdit_2
/// \brief NewObject::on_OtherNameLineEdit_1_editingFinished
///
void ObjectForm::on_OtherNameLineEdit_1_editingFinished()
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
void ObjectForm::on_TypeComboBox_currentTextChanged(const QString &arg1)
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
void ObjectForm::on_NoteHorizontalSlider_valueChanged(int value)
{
    m_ui->NoteDisplayLabel->setText(QString(QString::number(value) + "/10"));
    m_note = value;
}


///
/// When the cancel button is clicked
/// \brief NewObject::on_CancelPushButton_clicked
///
void ObjectForm::on_CancelPushButton_clicked()
{
    close();
}


///
/// Save Button
/// \brief NewObject::on_SavePushButton_clicked
///
void ObjectForm::on_SavePushButton_clicked()
{
    try
    {
        if (CheckInput())
        {
            m_db->open();

            QSqlQuery query;

            query.prepare(
                        QString("INSERT INTO objects "
                        "(`object_id`, "
                        "`object_name`, "
                        "`object_messier`, "
                        "`object_ngc`, "
                        "`object_othername1`, "
                        "`object_othername2`, "
                        "`object_category`, "
                        "`object_constellation`, "
                        "`object_apparent_magnitude`, "
                        "`object_secondary_magnitude`, "
                        "`object_distance`, "
                        "`object_diameter`, "
                        "`object_right_ascension`, "
                        "`object_declination`, "
                        "`object_skymap1_id`, "
                        "`object_skymap2_id`, "
                        "`object_skymap3_id`, "
                        "`object_appreciation`, "
                        "`object_note`) "
                        "VALUES "
                        "(" + QString::number(m_objectId) + ", \""
                        + m_name +"\", "
                        + QString::number(m_messier) + ", "
                        + QString::number(m_ngc) + ", \""
                        + m_otherName1 + "\", \""
                        + m_otherName2 + "\", "
                        + QString::number(m_category) + ", "
                        + QString::number(m_constellation) + ", "
                        + QString::number(m_apparentMagnitude) + ", "
                        + QString::number(m_secondApparentMagnitude) + ", "
                        + QString::number(m_distance) + ", "
                        + QString::number(m_diameter) + ", \""
                        + m_rightAscension + "\", \""
                        + m_declination + "\", "
                        + QString::number(m_skyMap1) + ", "
                        + QString::number(m_skyMap2) + ", "
                        + QString::number(m_skyMap3) + ", \""
                        + m_description + "\", "
                        + QString::number(m_note) + ");")
                        );

            if (query.exec() == false)
            {
                Error sqlError(ErrorPriority::Warning, &query);
                sqlError.printMessage();
            }

            qDebug() << query.lastError();
            qDebug() << query.lastQuery();

            m_db->close();
        }
    }
    catch (Error e)
    {
        e.printMessage();
    }
}

