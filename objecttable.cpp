#include "objecttable.h"
#include "ui_tabledialog.h"


///
/// Constructor
/// \brief ObjectTable::ObjectTable
/// \param parent
/// \param db
///
ObjectTable::ObjectTable(QWidget *parent, QSqlDatabase *db)
    : TableDialog(parent, db)
{
    tablePopulate();
}


///
/// Table filler function
/// \brief ObjectTable::tablePopulate
///
void ObjectTable::tablePopulate()
{
    // Open the database connection
    m_db->open();

    // Query container object
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

    // Window style
    setWindowTitle("Types");
    m_ui->label->setText("Tous les types");

    // Table style
    m_ui->tableView->setSelectionMode(QAbstractItemView::NoSelection);
    m_ui->tableView->resizeColumnToContents(0);
    m_ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // Close the database connection
    m_db->close();
}
