#include "mapstable.h"
#include "ui_mapstable.h"

MapsTable::MapsTable(QWidget *parent, QSqlDatabase *db)
    : QWidget(parent)
    , m_ui(new Ui::mapsTable)
    , m_db(db)
{
    m_ui->setupUi(this);

    // Get skymap data from the database
    try
    {
        updateTable1();
        updateTable2();
        updateTable3();

        // Table style
        m_ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        m_ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        m_ui->tableView_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
    catch (Error &e)
    {
        e.printMessage();
    }
}


MapsTable::~MapsTable()
{
    delete m_ui;
}


// Updating methods
void MapsTable::updateTable1()
{
    m_db->open();

    QSqlQuery query1;

    query1.prepare(
        "SELECT "
        "`skymap1_number` AS `Numero`, "
        "`skymap1_right_ascension` AS `Ascension droite`, "
        "`skymap1_declination` AS `Déclinaison` "
        "FROM skymap1 "
        "ORDER BY skymap1.`skymap1_number` + 0 ASC;"
    );

    if (query1.exec() == false)
    {
        throw SqlError(ErrorPriority::Critical, "Impossible de selectionner les carte 1", &query1);
    }

    // Setup query models to hold the data
    QSqlQueryModel *model1 = new QSqlQueryModel();
    model1->setQuery(query1);
    // Put the models into table views
    m_ui->tableView->setModel(model1);

    m_db->close();
}


void MapsTable::updateTable2()
{
    m_db->open();

    QSqlQuery query2;

    query2.prepare(
        "SELECT "
        "`skymap2_number` AS `Numero`, "
        "`skymap2_right_ascension` AS `Ascension droite`, "
        "`skymap2_declination` AS `Déclinaison` "
        "FROM skymap2 "
        "ORDER BY skymap2.`skymap2_number` + 0 ASC;"
    );

    if (query2.exec() == false)
    {
        throw SqlError(ErrorPriority::Critical, "Impossible de selectionner les carte 1", &query2);
    }

    // Setup query models to hold the data
    QSqlQueryModel *model2 = new QSqlQueryModel();
    model2->setQuery(query2);
    // Put the models into table views
    m_ui->tableView_2->setModel(model2);

    m_db->close();
}

void MapsTable::updateTable3()
{
    m_db->open();

    QSqlQuery query3;

    query3.prepare(
        "SELECT "
        "`skymap3_number` AS `Numero`, "
        "`skymap3_right_ascension` AS `Ascension droite`, "
        "`skymap3_declination` AS `Déclinaison` "
        "FROM skymap3 "
        "ORDER BY skymap3.`skymap3_number` + 0 ASC;"
    );

    if (query3.exec() == false)
    {
        throw SqlError(ErrorPriority::Critical, "Impossible de selectionner les carte 1", &query3);
    }

    // Setup query models to hold the data
    QSqlQueryModel *model3 = new QSqlQueryModel();
    model3->setQuery(query3);
    // Put the models into table views
    m_ui->tableView_3->setModel(model3);

    m_db->close();
}


void MapsTable::resetInputs()
{
    // Add 1 to the number
    m_ui->nameSpinBox->setValue(m_ui->nameSpinBox->value() + 1);
    m_ui->nameSpinBox_2->setValue(m_ui->nameSpinBox_2->value() + 1);
    m_ui->nameSpinBox_3->setValue(m_ui->nameSpinBox_3->value() + 1);

    // Right ascension
    // Hour
    m_ui->raDegreeSpinBox->setValue(0);
    m_ui->raDegreeSpinBox_2->setValue(0);
    m_ui->raDegreeSpinBox_3->setValue(0);
    // Minutes
    m_ui->raMinuteSpinBox->setValue(0);
    m_ui->raMinuteSpinBox_2->setValue(0);
    m_ui->raMinuteSpinBox_3->setValue(0);
    // Secondes
    m_ui->raSecondDoubleSpinBox->setValue(0.00);
    m_ui->raSecondDoubleSpinBox_2->setValue(0.00);
    m_ui->raSecondDoubleSpinBox_3->setValue(0.00);

    // Declination
    // Hour
    m_ui->decDegreeSpinBox->setValue(0);
    m_ui->decDegreeSpinBox_2->setValue(0);
    m_ui->decDegreeSpinBox_3->setValue(0);
    // Minutes
    m_ui->decMinuteSpinBox->setValue(0);
    m_ui->decMinuteSpinBox_2->setValue(0);
    m_ui->decMinuteSpinBox_3->setValue(0);
    // Secondes
    m_ui->decSecondDoubleSpinBox->setValue(0.00);
    m_ui->decSecondDoubleSpinBox_2->setValue(0.00);
    m_ui->decSecondDoubleSpinBox_3->setValue(0.00);
}


// Check the input for a new row
bool MapsTable::checkInput(const unsigned int table, const unsigned int number)
{
    // Table validity verification
    if (table > 3 || table == 0)
    {
        throw InputError(ErrorPriority::Warning, QString("L'index de la table à modifier est impossible : " + QString::number(table)));
        return false;
    }

    QString tableName = "skymap" + QString::number(table);

    // Number verification
    {
        m_db->open();

        QSqlQuery query;
        query.prepare(QString("SELECT `" + tableName + "_id` FROM `" + tableName + "` WHERE `"+ tableName + "_number` = " + QString::number(number) + ";"));
        query.exec();
        if (query.next())
        {
            throw InputError(ErrorPriority::Warning, "Ce numero de carte est déjà enregistré dans la base de données");
            return false;
        }

        m_db->close();
    }

    // Right ascension verification
    // Declination verification
    // Nothing to do, already verified by spinboxes max and min

    return true;
}


// Row addition


// In table 1
void MapsTable::on_addPushButton_1_clicked()
{
    try {
        unsigned int number = m_ui->nameSpinBox->value();

        if (checkInput(1, number))
        {
            Angle tmpRightAscension(true, m_ui->raDegreeSpinBox->value(), m_ui->raMinuteSpinBox->value(), m_ui->raSecondDoubleSpinBox->value());
            Angle tmpDeclination(false, m_ui->decDegreeSpinBox->value(), m_ui->decMinuteSpinBox->value(), m_ui->decSecondDoubleSpinBox->value());

            QString rightAscension = tmpRightAscension.getHourAngle();
            QString declination = tmpDeclination.getDegreeAngle();

            // Insertion query
            m_db->open();

            QSqlQuery query;

            query.prepare(
                "SELECT "
                "MAX(`skymap1_id`) "
                "FROM "
                "`skymap1` "
                "WHERE 1;"
            );

            if (query.exec() == false)
            {
                throw SqlError(ErrorPriority::Warning, "Impossible de récuperer l'ID de la nouvelle ligne", &query);
            }

            unsigned int skymapId = query.value(0).toUInt() + 1;

            query.prepare(
                "INSERT INTO `skymap1` "
                "(`skymap1_id`, "
                "`skymap1_number`, "
                "`skymap1_right_ascension`, "
                "`skymap1_declination`)"
                "VALUES"
                "(:skymapId, "
                ":skymapNumber, "
                ":skymapRA, "
                ":skymapDec);"
            );

            query.bindValue(":skymapId", skymapId);
            query.bindValue(":skymapNumber", number);
            query.bindValue(":skymapRA", rightAscension);
            query.bindValue(":skymapDec", declination);

            if (query.exec() == false)
            {
                throw SqlError(ErrorPriority::Warning, "Impossible de supprimer la ligne dans la base de donnée", &query);
            }

            m_db->close();

            resetInputs();
            updateTable1();
        }
        else
        {
            throw Error(ErrorPriority::Undefined, "La verification des entrés à échoué");
        }
    }
    catch (Error &e)
    {
        e.printMessage();
    }
}


// In table 2
void MapsTable::on_addPushButton_2_clicked()
{
    try {
        unsigned int number = m_ui->nameSpinBox->value();

        if (checkInput(2, number))
        {
            Angle tmpRightAscension(true, m_ui->raDegreeSpinBox_2->value(), m_ui->raMinuteSpinBox_2->value(), m_ui->raSecondDoubleSpinBox_2->value());
            Angle tmpDeclination(false, m_ui->decDegreeSpinBox_2->value(), m_ui->decMinuteSpinBox_2->value(), m_ui->decSecondDoubleSpinBox_2->value());

            QString rightAscension = tmpRightAscension.getHourAngle();
            QString declination = tmpDeclination.getDegreeAngle();

            // Insertion query
            m_db->open();

            QSqlQuery query;

            query.prepare(
                "SELECT "
                "MAX(`skymap2_id`) "
                "FROM "
                "`skymap2` "
                "WHERE 1;"
            );

            if (query.exec() == false)
            {
                throw SqlError(ErrorPriority::Warning, "Impossible de récuperer l'ID de la nouvelle ligne", &query);
            }

            unsigned int skymapId = query.value(0).toUInt() + 1;

            query.prepare(
                "INSERT INTO `skymap2` "
                "(`skymap2_id`, "
                "`skymap2_number`, "
                "`skymap2_right_ascension`, "
                "`skymap2_declination`)"
                "VALUES"
                "(:skymapId, "
                ":skymapNumber, "
                ":skymapRA, "
                ":skymapDec);"
            );

            query.bindValue(":skymapId", skymapId);
            query.bindValue(":skymapNumber", number);
            query.bindValue(":skymapRA", rightAscension);
            query.bindValue(":skymapDec", declination);

            if (query.exec() == false)
            {
                throw SqlError(ErrorPriority::Warning, "Impossible de supprimer la ligne dans la base de donnée", &query);
            }

            m_db->close();

            resetInputs();
            updateTable1();
        }
    }
    catch (Error &e)
    {
        e.printMessage();
    }
}


// In table 3
void MapsTable::on_addPushButton_3_clicked()
{
    try {
        unsigned int number = m_ui->nameSpinBox->value();

        if (checkInput(3, number))
        {
            Angle tmpRightAscension(true, m_ui->raDegreeSpinBox_3->value(), m_ui->raMinuteSpinBox_3->value(), m_ui->raSecondDoubleSpinBox_3->value());
            Angle tmpDeclination(false, m_ui->decDegreeSpinBox_3->value(), m_ui->decMinuteSpinBox_3->value(), m_ui->decSecondDoubleSpinBox_3->value());

            QString rightAscension = tmpRightAscension.getHourAngle();
            QString declination = tmpDeclination.getDegreeAngle();

            // Insertion query
            m_db->open();

            QSqlQuery query;

            query.prepare(
                "SELECT "
                "MAX(`skymap3_id`) "
                "FROM "
                "`skymap3` "
                "WHERE 1;"
            );

            if (query.exec() == false)
            {
                throw SqlError(ErrorPriority::Warning, "Impossible de récuperer l'ID de la nouvelle ligne", &query);
            }

            unsigned int skymapId = query.value(0).toUInt() + 1;

            query.prepare(
                "INSERT INTO `skymap3` "
                "(`skymap3_id`, "
                "`skymap3_number`, "
                "`skymap3_right_ascension`, "
                "`skymap3_declination`)"
                "VALUES"
                "(:skymapId, "
                ":skymapNumber, "
                ":skymapRA, "
                ":skymapDec);"
            );

            query.bindValue(":skymapId", skymapId);
            query.bindValue(":skymapNumber", number);
            query.bindValue(":skymapRA", rightAscension);
            query.bindValue(":skymapDec", declination);

            if (query.exec() == false)
            {
                throw SqlError(ErrorPriority::Warning, "Impossible de supprimer la ligne dans la base de donnée", &query);
            }

            m_db->close();

            resetInputs();
            updateTable1();
        }
    }
    catch (Error &e)
    {
        e.printMessage();
    }
}


// Row deletion

// In table 1
void MapsTable::on_removePushButton_1_clicked()
{
    if (m_ui->tableView->selectionModel()->hasSelection())
    {
        try
        {
            // Row to delete
            const unsigned int selectedRowNumber = m_ui->tableView->model()->data(m_ui->tableView->selectionModel()->selectedRows().first().siblingAtColumn(0)).toUInt();
            // Row count before deletion
            const unsigned int countBeforeDeletion = m_ui->tableView->model()->rowCount();

            m_db->open();

            QSqlQuery query;

            query.prepare
            (
                "DELETE FROM `skymap1` "
                "WHERE NOT EXISTS "
                "("
                "SELECT * "
                "FROM `objects` "
                "WHERE `object_skymap1_id` = `skymap1`.`skymap1_id`"
                ") "
                "AND `skymap1`.`skymap1_number` = :rowToDelete;"
            );
            query.bindValue(":rowToDelete", selectedRowNumber);

            if (query.exec() == false)
            {
                throw SqlError(ErrorPriority::Warning, "Impossible de supprimer la ligne dans la base de donnée", &query);
            }

            m_db->close();

            // If the query deleted nothing
            if ((unsigned int)m_ui->tableView->model()->rowCount() == countBeforeDeletion)
            {
                throw InputError(ErrorPriority::Warning, "Attention, vous essayez de supprimer une carte qui est attribué à au moins un objets.\ndésaffectez d'aborord cette carte à tous les objets");
            }

            updateTable1();
        }
        catch (Error &e)
        {
            e.printMessage();
        }
    }
}


// In table 2
void MapsTable::on_removePushButton_2_clicked()
{
    if (m_ui->tableView->selectionModel()->hasSelection())
    {
        try
        {
            // Row to delete
            const unsigned int selectedRowNumber = m_ui->tableView_2->model()->data(m_ui->tableView_2->selectionModel()->selectedRows().first().siblingAtColumn(0)).toUInt();
            // Row count before deletion
            const unsigned int countBeforeDeletion = m_ui->tableView->model()->rowCount();

            m_db->open();

            QSqlQuery query;

            query.prepare
            (
                "DELETE FROM `skymap1` "
                "WHERE NOT EXISTS "
                "("
                    "SELECT * "
                    "FROM `objects` "
                    "WHERE `object_skymap1_id` = `skymap1`.`skymap1_id`"
                ") "
                "AND `skymap1`.`skymap1_number` = :rowToDelete;"
            );
            query.bindValue(":rowToDelete", QString::number(selectedRowNumber));

            if (query.exec() == false)
            {
                throw SqlError(ErrorPriority::Warning, "Impossible de supprimer la ligne dans la base de donnée", &query);
            }

            m_db->close();

            // If the query deleted nothing
            if ((unsigned int)m_ui->tableView->model()->rowCount() == countBeforeDeletion)
            {
                throw InputError(ErrorPriority::Warning, "Attention, vous essayez de supprimer une carte qui est attribué à au moins un objets.\ndésaffectez d'aborord cette carte à tous les objets");
            }

            updateTable2();
        }
        catch (Error &e)
        {
            e.printMessage();
        }
    }
}


// In table 3
void MapsTable::on_removePushButton_3_clicked()
{
    if (m_ui->tableView->selectionModel()->hasSelection())
    {
        try
        {
            // Row to delete
            const unsigned int selectedRowNumber = m_ui->tableView->model()->data(m_ui->tableView->selectionModel()->selectedRows().first().siblingAtColumn(0)).toUInt();
            // Row count before deletion
            const unsigned int countBeforeDeletion = m_ui->tableView->model()->rowCount();

            m_db->open();

            QSqlQuery query;

            query.prepare
            (
                "DELETE FROM `skymap1` "
                "WHERE NOT EXISTS "
                "("
                    "SELECT * "
                    "FROM `objects` "
                    "WHERE `object_skymap1_id` = `skymap1`.`skymap1_id`"
                ") "
                "AND `skymap1`.`skymap1_number` = :rowToDelete;"
            );
            query.bindValue(":rowToDelete", QString::number(selectedRowNumber));

            if (query.exec() == false)
            {
                throw SqlError(ErrorPriority::Warning, "Impossible de supprimer la ligne dans la base de donnée", &query);
            }

            m_db->close();

            // If the query deleted nothing
            if ((unsigned int)m_ui->tableView->model()->rowCount() == countBeforeDeletion)
            {
                throw InputError(ErrorPriority::Warning, "Attention, vous essayez de supprimer une carte qui est attribué à au moins un objets.\ndésaffectez d'aborord cette carte à tous les objets");
            }

            updateTable3();
        }
        catch (Error &e)
        {
            e.printMessage();
        }
    }
}


// Quitt the window
void MapsTable::on_quittPushButton_clicked()
{
    close();
}




