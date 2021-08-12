#include "typetable.h"
#include "ui_tabledialog.h"


TypeTable::TypeTable(QWidget *parent, QSqlDatabase *db)
    : TableDialog(parent, db)
{
    setWindowIcon(QIcon(":/Ressources/icons/icons8-nebula-96.png"));
    setWindowTitle("Tous les types");
    m_ui->label->setText("Tous les types");
    tablePopulate();
}


void TypeTable::tablePopulate()
{
    m_db->open();

    QSqlQuery query;

    // Set the query
    query.prepare(
                "SELECT "
                "`category_name` AS `Nom`, "
                "`category_description` AS `Description` "
                "FROM `categories` "
                "WHERE 1");

    if (query.exec() == false)
    {
        SqlError sqlError(ErrorPriority::Critical, "Impossible de selectionner les types", &query);
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
    m_ui->tableView->verticalHeader()->setVisible(false);
    m_ui->tableView->horizontalHeader()->setStretchLastSection(true);
    m_ui->tableView->resizeColumnToContents(0);
    m_ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    m_db->close();
}
