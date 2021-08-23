/**
 * /*
 *  * Created on Tue Jul 31 2021
 *  *
 *  * Copyright (c) 2021 - Mathéo G - All Right Reserved
 *  *
 *  * Licensed under the Apache License, Version 2.0
 *  * Available on GitHub at https://github.com/Paracetamol56/Observeur2
 *  */ */

#include "constellationtable.h"
#include "ui_tabledialog.h"


ConstellationTable::ConstellationTable(QWidget *parent, QSqlDatabase *database)
    : TableDialog(parent, database)
{
    setWindowIcon(QIcon(":/Ressources/icons/icons8-constellation-96.png"));
    setWindowTitle("Toutes les constellations");
    m_ui->label->setText("Toutes les constellations");
    tablePopulate();
}


void ConstellationTable::tablePopulate()
{
    m_db->open();

    QSqlQuery query;

    // Set the query
    query.prepare(
                "SELECT "
                "`constellation_name` AS `Nom`, "
                "`constellation_latin_name` AS `Nom latin`, "
                "`constellation_abreviation` AS `Abreviation`, "
                "`constellation_extent_squaredeg` AS `Etendue (deg²)`, "
                "`constellation_extent_percent` AS `Pourcentage`, "
                "`constellation_right_ascension` AS `Ascension droite`, "
                "`constellation_declination` AS `Déclinaison` "
                "FROM `constellations` "
                "WHERE 1;");

    if (query.exec() == false)
    {
        SqlError sqlError(ErrorPriority::Critical, "Impossible de selectionner les constellations", &query);
        sqlError.printMessage();
    }

    // Setup a query model to hold the data
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);

    // Convert to a QSortFilterProxyModel
    QSortFilterProxyModel *sortModel = new QSortFilterProxyModel();
    sortModel->setSourceModel(model);

    // Put the model into the table view
    m_ui->tableView->setModel(sortModel);

    // Table style
    m_ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    m_db->close();
}
