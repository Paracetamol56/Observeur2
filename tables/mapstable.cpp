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

    query1.prepare(
        "SELECT "
        "MAX(`skymap1_number` + 0) "
        "FROM skymap1 "
        "WHERE 1;"
    );

    if (query1.exec() == false)
    {
        throw SqlError(ErrorPriority::Critical, "Impossible de selectionner les carte 1", &query1);
    }

    // Put the max value + 1 in the number spinbox
    query1.first();
    m_ui->nameSpinBox->setValue(query1.value(0).toInt() + 1);

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
        throw SqlError(ErrorPriority::Critical, "Impossible de selectionner les carte 2", &query2);
    }

    // Setup query models to hold the data
    QSqlQueryModel *model2 = new QSqlQueryModel();
    model2->setQuery(query2);
    // Put the models into table views
    m_ui->tableView_2->setModel(model2);

    query2.prepare(
        "SELECT "
        "MAX(`skymap2_number` + 0) "
        "FROM skymap2 "
        "WHERE 1;"
    );

    if (query2.exec() == false)
    {
        throw SqlError(ErrorPriority::Critical, "Impossible de selectionner les carte 2", &query2);
    }

    // Put the max value + 1 in the number spinbox
    query2.first();
    m_ui->nameSpinBox->setValue(query2.value(0).toInt() + 1);

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
        throw SqlError(ErrorPriority::Critical, "Impossible de selectionner les carte 3", &query3);
    }

    // Setup query models to hold the data
    QSqlQueryModel *model3 = new QSqlQueryModel();
    model3->setQuery(query3);
    // Put the models into table views
    m_ui->tableView_3->setModel(model3);

    query3.prepare(
        "SELECT "
        "MAX(`skymap3_number` + 0) "
        "FROM skymap3 "
        "WHERE 1;"
    );

    if (query3.exec() == false)
    {
        throw SqlError(ErrorPriority::Critical, "Impossible de selectionner les carte 3", &query3);
    }

    // Put the max value + 1 in the number spinbox
    query3.first();
    m_ui->nameSpinBox_3->setValue(query3.value(0).toInt() + 1);

    m_db->close();
}


void MapsTable::resetInputs()
{
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
                "MAX(`skymap1_id` + 0) "
                "FROM "
                "`skymap1` "
                "WHERE 1;"
            );

            if (query.exec() == false)
            {
                throw SqlError(ErrorPriority::Warning, "Impossible de récuperer l'ID de la nouvelle ligne", &query);
            }

            query.first();
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
        unsigned int number = m_ui->nameSpinBox_2->value();

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
                "MAX(`skymap2_id` + 0) "
                "FROM "
                "`skymap2` "
                "WHERE 1;"
            );

            if (query.exec() == false)
            {
                throw SqlError(ErrorPriority::Warning, "Impossible de récuperer l'ID de la nouvelle ligne", &query);
            }

            query.first();
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
            updateTable2();
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
        unsigned int number = m_ui->nameSpinBox_3->value();

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
                "MAX(`skymap3_id` + 0) "
                "FROM "
                "`skymap3` "
                "WHERE 1;"
            );

            if (query.exec() == false)
            {
                throw SqlError(ErrorPriority::Warning, "Impossible de récuperer l'ID de la nouvelle ligne", &query);
            }

            query.first();
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
            updateTable3();
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
                "SELECT `skymap1_id` "
                "FROM `skymap1` "
                "WHERE `skymap1_number` = :rowToDelete;"
            );
            query.bindValue(":rowToDelete", selectedRowNumber);
            if (query.exec() == false)
            {
                throw SqlError(ErrorPriority::Warning, "Impossible de supprimer la ligne dans la base de donnée", &query);
            }
            query.first();
            const unsigned int idToDelete = query.value(0).toUInt();

            query.prepare
            (
                "DELETE FROM `skymap1` "
                "WHERE "
                "NOT EXISTS "
                "("
                    "SELECT * "
                    "FROM `objects` "
                    "WHERE `object_skymap1_id` = `skymap1`.`skymap1_id`"
                ") "
                "AND `skymap1`.`skymap1_id` = :rowToDelete;"
            );
            query.bindValue(":rowToDelete", idToDelete);

            if (query.exec() == false)
            {
                throw SqlError(ErrorPriority::Warning, "Impossible de supprimer la ligne dans la base de donnée", &query);
            }

            m_db->close();

            updateTable1();

            // If the query deleted nothing
            if ((unsigned int)m_ui->tableView->model()->rowCount() == countBeforeDeletion)
            {
                throw InputError(ErrorPriority::Warning, "Attention, vous essayez de supprimer une carte qui est attribué à au moins un objets.\ndésaffectez d'aborord cette carte à tous les objets");
            }
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
                "SELECT `skymap2_id` "
                "FROM `skymap2` "
                "WHERE `skymap2_number` = :rowToDelete;"
            );
            query.bindValue(":rowToDelete", selectedRowNumber);
            if (query.exec() == false)
            {
                throw SqlError(ErrorPriority::Warning, "Impossible de supprimer la ligne dans la base de donnée", &query);
            }
            query.next();
            const unsigned int idToDelete = query.value(0).toUInt();

            query.prepare
            (
                "DELETE FROM `skymap2` "
                "WHERE "
                "NOT EXISTS "
                "("
                    "SELECT * "
                    "FROM `objects` "
                    "WHERE `object_skymap2_id` = `skymap2`.`skymap2_id`"
                ") "
                "AND `skymap2`.`skymap2_id` = :rowToDelete;"
            );
            query.bindValue(":rowToDelete", idToDelete);

            if (query.exec() == false)
            {
                throw SqlError(ErrorPriority::Warning, "Impossible de supprimer la ligne dans la base de donnée", &query);
            }

            m_db->close();

            updateTable2();

            // If the query deleted nothing
            if ((unsigned int)m_ui->tableView->model()->rowCount() == countBeforeDeletion)
            {
                throw InputError(ErrorPriority::Warning, "Attention, vous essayez de supprimer une carte qui est attribué à au moins un objets.\ndésaffectez d'aborord cette carte à tous les objets");
            }
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
                "SELECT `skymap3_id` "
                "FROM `skymap3` "
                "WHERE `skymap3_number` = :rowToDelete;"
            );
            query.bindValue(":rowToDelete", selectedRowNumber);
            if (query.exec() == false)
            {
                throw SqlError(ErrorPriority::Warning, "Impossible de supprimer la ligne dans la base de donnée", &query);
            }
            query.next();
            const unsigned int idToDelete = query.value(0).toUInt();

            query.prepare
            (
                "DELETE FROM `skymap3` "
                "WHERE "
                "NOT EXISTS "
                "("
                    "SELECT * "
                    "FROM `objects` "
                    "WHERE `object_skymap3_id` = `skymap3`.`skymap3_id`"
                ") "
                "AND `skymap3`.`skymap3_id` = :rowToDelete;"
            );
            query.bindValue(":rowToDelete", idToDelete);

            if (query.exec() == false)
            {
                throw SqlError(ErrorPriority::Warning, "Impossible de supprimer la ligne dans la base de donnée", &query);
            }

            m_db->close();

            updateTable3();

            // If the query deleted nothing
            if ((unsigned int)m_ui->tableView->model()->rowCount() == countBeforeDeletion)
            {
                throw InputError(ErrorPriority::Warning, "Attention, vous essayez de supprimer une carte qui est attribué à au moins un objets.\ndésaffectez d'aborord cette carte à tous les objets");
            }
        }
        catch (Error &e)
        {
            e.printMessage();
        }
    }
}


// Row modification

// In table 1
void MapsTable::on_modifyPushButton_clicked()
{
    // === Get the selected row ID
    // Row to modify
    const unsigned int selectedRowNumber = m_ui->tableView->model()->data(m_ui->tableView->selectionModel()->selectedRows().first().siblingAtColumn(0)).toUInt();
    // Get the ID in the database
    m_db->open();
    QSqlQuery query;
    query.prepare
    (
        "SELECT `skymap1_id` "
        "FROM `skymap1` "
        "WHERE `skymap1_number` = :rowToModify;"
    );
    query.bindValue(":rowToModify", selectedRowNumber);
    if (query.exec() == false)
    {
        throw SqlError(ErrorPriority::Warning, "Impossible de récuperer l'ID de la ligne à modifier", &query);
    }
    query.next();
    const unsigned int idToModify = query.value(0).toUInt();
    m_db->close();

    // === Show the modification dialog
    MapModificationDialog *modificationDialog = new MapModificationDialog(this, m_db, 1, idToModify);
    connect(modificationDialog, SIGNAL(newValuesSaved()), this, SLOT(on_newValuesSaved()));
    modificationDialog->exec();
}


// In table 2
void MapsTable::on_modifyPushButton_2_clicked()
{
    // === Get the selected row ID
    // Row to modify
    const unsigned int selectedRowNumber = m_ui->tableView_2->model()->data(m_ui->tableView_2->selectionModel()->selectedRows().first().siblingAtColumn(0)).toUInt();
    // Get the ID in the database
    m_db->open();
    QSqlQuery query;
    query.prepare
    (
        "SELECT `skymap2_id` "
        "FROM `skymap2` "
        "WHERE `skymap2_number` = :rowToModify;"
    );
    query.bindValue(":rowToModify", selectedRowNumber);
    if (query.exec() == false)
    {
        throw SqlError(ErrorPriority::Warning, "Impossible de récuperer l'ID de la ligne à modifier", &query);
    }
    query.next();
    const unsigned int idToModify = query.value(0).toUInt();
    m_db->close();

    // === Show the modification dialog
    MapModificationDialog *modificationDialog = new MapModificationDialog(this, m_db, 2, idToModify);
    connect(modificationDialog, SIGNAL(newValuesSaved()), this, SLOT(on_newValuesSaved()));
    modificationDialog->exec();
}


// In table 3
void MapsTable::on_modifyPushButton_3_clicked()
{
    // === Get the selected row ID
    // Row to modify
    const unsigned int selectedRowNumber = m_ui->tableView_3->model()->data(m_ui->tableView_3->selectionModel()->selectedRows().first().siblingAtColumn(0)).toUInt();
    // Get the ID in the database
    m_db->open();
    QSqlQuery query;
    query.prepare
    (
        "SELECT `skymap3_id` "
        "FROM `skymap3` "
        "WHERE `skymap3_number` = :rowToModify;"
    );
    query.bindValue(":rowToModify", selectedRowNumber);
    if (query.exec() == false)
    {
        throw SqlError(ErrorPriority::Warning, "Impossible de récuperer l'ID de la ligne à modifier", &query);
    }
    query.next();
    const unsigned int idToModify = query.value(0).toUInt();
    m_db->close();

    // === Show the modification dialog
    MapModificationDialog *modificationDialog = new MapModificationDialog(this, m_db, 3, idToModify);
    connect(modificationDialog, SIGNAL(newValuesSaved()), this, SLOT(on_newValuesSaved()));
    modificationDialog->exec();
}


// Quitt the window
void MapsTable::on_quittPushButton_clicked()
{
    close();
}


void MapsTable::on_newValuesSaved()
{
    updateTable1();
    updateTable2();
    updateTable3();
}


// === Right click implementation

// In table 1
void MapsTable::on_tableView_customContextMenuRequested(const QPoint &pos)
{
    QMenu *contextMenu = new QMenu(this);

    QAction *modifyAction = new QAction(tr("Modifier"), this);
    QAction *deleteAction = new QAction(tr("Supprimer"), this);

    connect(modifyAction, SIGNAL(triggered()), this, SLOT(on_modifyPushButton_clicked()));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(on_removePushButton_1_clicked()));

    contextMenu->addAction(modifyAction);
    contextMenu->addAction(deleteAction);

    contextMenu->popup(m_ui->tableView->viewport()->mapToGlobal(pos));
}


// In table 2
void MapsTable::on_tableView_2_customContextMenuRequested(const QPoint &pos)
{
    QMenu contextMenu;

    QAction *modifyAction = new QAction(tr("Modifier"), this);
    QAction *deleteAction = new QAction(tr("Supprimer"), this);

    connect(modifyAction, SIGNAL(triggered()), this, SLOT(on_modifyPushButton_2_clicked()));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(on_removePushButton_2_clicked()));

    contextMenu.addAction(modifyAction);
    contextMenu.addAction(deleteAction);

    contextMenu.popup(m_ui->tableView->viewport()->mapToGlobal(pos));
}


// In table 3
void MapsTable::on_tableView_3_customContextMenuRequested(const QPoint &pos)
{
    QMenu contextMenu;

    QAction *modifyAction = new QAction(tr("Modifier"), this);
    QAction *deleteAction = new QAction(tr("Supprimer"), this);

    connect(modifyAction, SIGNAL(triggered()), this, SLOT(on_modifyPushButton_3_clicked()));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(on_removePushButton_3_clicked()));

    contextMenu.addAction(modifyAction);
    contextMenu.addAction(deleteAction);

    contextMenu.popup(m_ui->tableView->viewport()->mapToGlobal(pos));
}

