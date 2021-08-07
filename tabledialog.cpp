#include "tabledialog.h"
#include "ui_tabledialog.h"

///
/// Constructor
/// \brief TableDialog::TableDialog
/// \param parent
///
TableDialog::TableDialog(QWidget *parent, QSqlDatabase *database)
    : QDialog(parent)
    , m_ui(new Ui::TableDialog)
    , m_db(database)
{
    // ########################## Setup the UI ######################### //

    m_ui->setupUi(this);
}


///
/// Destructor
/// \brief TableDialog::~TableDialog
///
TableDialog::~TableDialog()
{
    delete m_ui;
}


///
/// Table filler function
/// \brief TableDialog::tablePopulate
///
void TableDialog::tablePopulate()
{
    // Open the database connection
    m_db->open();

    // Query container object
    QSqlQuery query;

    // Set the query
    query.prepare(
                "SELECT "
                "*"
                "FROM `objects` "
                "WHERE 1");
    query.exec();

    // Setup a query model to hold the data
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);

    // Convert to a QSortFilterProxyModel
    QSortFilterProxyModel *sortModel = new QSortFilterProxyModel();
    sortModel->setSourceModel(model);

    // Put the model into the table view
    m_ui->tableView->setModel(sortModel);

    // Table style
    m_ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // Close the database connection
    m_db->close();
}
