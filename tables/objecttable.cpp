/**
 * /*
 *  * Created on Tue Jul 31 2021
 *  *
 *  * Copyright (c) 2021 - Mathéo G - All Right Reserved
 *  *
 *  * Licensed under the Apache License, Version 2.0
 *  * Available on GitHub at https://github.com/Paracetamol56/Observeur2
 *  */ */

#include "objecttable.h"
#include "ui_tabledialog.h"


ObjectTable::ObjectTable(QWidget *parent, QSqlDatabase *db)
    : TableDialog(parent, db)
{
    setWindowIcon(QIcon(":/Ressources/icons/icons8-show-property-96.png"));
    setWindowTitle("Tous les objets");
    m_ui->label->setText("Tous les objets");
    tablePopulate();
}


void ObjectTable::tablePopulate()
{
    m_db->open();

    QSqlQuery query;

    // Set the query
    query.prepare(
                "SELECT "
                "* "
                "FROM `objects` "
                "WHERE 1");

    if (query.exec() == false)
    {
        SqlError sqlError(ErrorPriority::Critical, "Impossible de selectionner les objets", &query);
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
    m_ui->tableView->setSelectionMode(QAbstractItemView::NoSelection);
    m_ui->tableView->resizeColumnToContents(0);
    m_ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    m_db->close();
}
