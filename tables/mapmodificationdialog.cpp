#include "mapmodificationdialog.h"
#include "ui_mapmodificationdialog.h"

MapModificationDialog::MapModificationDialog(QWidget *parent, QSqlDatabase *db, const unsigned int table, const unsigned int id)
    : QDialog(parent)
    , m_ui(new Ui::MapModificationDialog)
    , m_db(db)
    , m_idToModify(id)
    , m_tableString("skymap" + QString::number(table))
{
    m_ui->setupUi(this);

    m_db->open();

    QSqlQuery query;
    query.prepare(
        "SELECT `"
        + m_tableString + "_number`, `"
        + m_tableString + "_right_ascension`, `"
        + m_tableString + "_declination` "
        "FROM `"
        + m_tableString +
        "` WHERE `"
        + m_tableString + "_id` = \"" + QString::number(m_idToModify) + "\";");
    if (query.exec() == false)
    {
        SqlError error(ErrorPriority::Warning, "Impossible de selectionner la carte à modifier avec l'ID : " + QString::number(m_idToModify), &query);
        error.printMessage();
        on_CancelPushButton_clicked();
    }
    query.first();

    qDebug() << query.lastQuery();

    qDebug() << query.value(0).toUInt();
    qDebug() << query.value(1).toString();
    qDebug() << query.value(2).toString();

    m_ui->numberSpinBox->setValue(query.value(0).toUInt());

    Angle rightAscension(query.value(1).toString());
    m_ui->raHourSpinBox->setValue(rightAscension.getHour());
    m_ui->raMinuteSpinBox->setValue(rightAscension.getHourMinute());
    m_ui->raSecondDoubleSpinBox->setValue(rightAscension.getHourSecond());

    Angle declination(query.value(2).toString());
    m_ui->decDegreeSpinBox->setValue(declination.getDegree());
    m_ui->decMinuteSpinBox->setValue(declination.getDegreeMinute());
    m_ui->decSecondDoubleSpinBox->setValue(declination.getDegreeSecond());

    m_db->close();
}

MapModificationDialog::~MapModificationDialog()
{
    delete m_ui;
}

void MapModificationDialog::on_SavePushButton_clicked()
{

}


void MapModificationDialog::on_CancelPushButton_clicked()
{
    close();
}

