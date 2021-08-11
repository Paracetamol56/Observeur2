#include "objectdialog.h"
#include "ui_objectdialog.h"


ObjectDialog::ObjectDialog(QWidget *parent, QSqlDatabase *database, const unsigned int objectId)
    : QDialog(parent)
    , m_ui(new Ui::ObjectDialog)
    , m_db(database)
    ,m_id(objectId)
{
    m_ui->setupUi(this);

    m_db->open();

    QSqlQuery query;

    // Set the query
    query.prepare(
                "SELECT "
                "`objects`.`object_id`, "                   // 0
                "`objects`.`object_name`, "                 // 1
                "`objects`.`object_messier`, "              // 2
                "`objects`.`object_ngc`, "                  // 3
                "`objects`.`object_othername1`, "           // 4
                "`objects`.`object_othername2`, "           // 5
                "`categories`.`category_name`, "            // 6
                "`constellations`.`constellation_name`, "   // 7
                "`objects`.`object_apparent_magnitude`, "   // 8
                "`objects`.`object_secondary_magnitude`, "  // 9
                "`objects`.`object_right_ascension`, "      // 10
                "`objects`.`object_declination`, "          // 11
                "`objects`.`object_appreciation`, "         // 12
                "`objects`.`object_note`, "                 // 13
                "`skymap1`.`skymap1_number`, "              // 14
                "`skymap2`.`skymap2_number`, "              // 15
                "`skymap3`.`skymap3_number`, "              // 16
                "`objects`.`object_distance`, "             // 17
                "`objects`.`object_diameter`"               // 18
                "FROM `objects` "
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
                "WHERE `objects`.`object_id` = :object_id;"
                );

    query.bindValue(":object_id", QString::number(objectId));

    if (query.exec() == false)
    {
        SqlError sqlError(ErrorPriority::Critical, "Impossible de selectionner l'objet", &query);
        sqlError.printMessage();
    }

    query.next();

    // Name
    m_ui->nameLineEdit->setText(query.value(1).toString());

    // Messier
    if (query.value(2).toString() != "")
        m_ui->messierLineEdit->setText(query.value(2).toString());
    else
    {
        m_ui->messierLabel->hide();
        m_ui->messierLineEdit->hide();
        m_ui->messierPushButton->hide();
    }

    // NGC
    if (query.value(3).toString() != "")
        m_ui->ngcLineEdit->setText(query.value(3).toString());
    else
    {
        m_ui->ngcLabel->hide();
        m_ui->ngcLineEdit->hide();
        m_ui->ngcPushButton->hide();
    }

    // Other name(s)
    if (query.value(4).toString() != "")
    {
        m_ui->othernameLineEdit_1->setText(query.value(4).toString());
        if (query.value(5).toString() != "")
            m_ui->othernameLineEdit_2->setText(query.value(5).toString());
        else
            m_ui->othernameLineEdit_2->hide();
    }
    else
    {
        m_ui->otherNameLabel->hide();
        m_ui->othernameLineEdit_1->hide();
        m_ui->othernameLineEdit_2->hide();
    }

    // Type
    if (query.value(6).toString() != "")
        m_ui->typeLineEdit->setText(query.value(6).toString());
    else
    {
        m_ui->typeLabel->hide();
        m_ui->typeLineEdit->hide();
    }

    // Constellation
    if (query.value(7).toString() != "")
        m_ui->constellationLineEdit->setText(query.value(7).toString());
    else
    {
        m_ui->constellationLabel->hide();
        m_ui->constellationLineEdit->hide();
    }

    // Apparent magnitude(s)
    if (query.value(8).toString() != "")
    {
        m_ui->apparentMagnitudeLineEdit_1->setText(query.value(8).toString());
        if (query.value(9).toString() != "")
            m_ui->apparentMagnitudeLineEdit_2->setText(query.value(9).toString());
        else
            m_ui->apparentMagnitudeLineEdit_2->hide();
    }
    else
    {
        m_ui->apparentMagnitudeLabel->hide();
        m_ui->apparentMagnitudeLineEdit_1->hide();
        m_ui->apparentMagnitudeLineEdit_2->hide();
    }

    // Distance
    if (query.value(17).toString() != "")
        m_ui->DistanceLineEdit->setText(query.value(7).toString());
    else
    {
        m_ui->distanceLabel->hide();
        m_ui->DistanceLineEdit->hide();
    }

    // Diameter
    if (query.value(18).toString() != "")
        m_ui->diamterLineEdit->setText(query.value(18).toString());
    else
    {
        m_ui->diameterLabel->hide();
        m_ui->diamterLineEdit->hide();
    }

    // Right ascension
    if (query.value(10).toString() != "")
        m_ui->RightAscensionLineEdit->setText(query.value(10).toString());
    else
    {
        m_ui->rightAscentionLabel->hide();
        m_ui->RightAscensionLineEdit->hide();
    }

    // Declination
    if (query.value(11).toString() != "")
        m_ui->declinationLineEdit->setText(query.value(11).toString());
    else
    {
        m_ui->declinationLabel->hide();
        m_ui->declinationLineEdit->hide();
    }

    // Shymap 1
    if (query.value(14).toString() != "")
        m_ui->skymap1LineEdit->setText(query.value(14).toString());
    else
    {
        m_ui->map1Label->hide();
        m_ui->skymap1LineEdit->hide();
    }

    // Shymap 2
    if (query.value(15).toString() != "")
        m_ui->skymap2LineEdit->setText(query.value(15).toString());
    else
    {
        m_ui->map2Label->hide();
        m_ui->skymap2LineEdit->hide();
    }

    // Shymap 3
    if (query.value(16).toString() != "")
        m_ui->skymap3LineEdit->setText(query.value(16).toString());
    else
    {
        m_ui->map3Label->hide();
        m_ui->skymap3LineEdit->hide();
    }

    // Note
    m_ui->noteLineEdit->setText(query.value(13).toString() + "/10");

    // Appreciation
    if (query.value(12).toString() != "")
        m_ui->appreciationTextBrowser->setMarkdown(query.value(12).toString());
    else
    {
        m_ui->map3Label->hide();
        m_ui->skymap3LineEdit->hide();
    }

    m_db->close();
}


ObjectDialog::~ObjectDialog()
{
    delete m_ui;
}

void ObjectDialog::on_messierPushButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://simbad.u-strasbg.fr/simbad/sim-basic?Ident=m" + m_ui->messierLineEdit->text() + "&submit=SIMBAD+search"));
}

void ObjectDialog::on_ngcPushButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://simbad.u-strasbg.fr/simbad/sim-basic?Ident=ngc" + m_ui->ngcLineEdit->text() + "&submit=SIMBAD+search"));
}
