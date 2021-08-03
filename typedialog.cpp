#include "typedialog.h"
#include "ui_typedialog.h"


///
/// Constructor
/// \brief TypeDialog::TypeDialog
/// \param parent
/// \param db
///
TypeDialog::TypeDialog(QWidget *parent, QSqlDatabase *db)
    : QDialog(parent)
    , m_ui(new Ui::TypeDialog)
{
    // ########################## Setup the UI ######################### //

    m_ui->setupUi(this);


    // ######### Get data from database to fill the constallation table ########## //

    tablePopulate(db);
}


///
/// Destructor
/// \brief TypeDialog::~TypeDialog
///
TypeDialog::~TypeDialog()
{
    delete m_ui;
}


///
/// Table filler function
/// \brief ConstellationDialog::tablePopulate
/// \param db
///
void TypeDialog::tablePopulate(QSqlDatabase *db)
{
    // Open the database connection
    db->open();

    // Query container object
    QSqlQuery query;

    // Set the query
    query.prepare(
                "SELECT "
                "`category_name` AS `Nom`, "
                "`category_description` AS `Description` "
                "FROM `categories` "
                "WHERE 1");
    query.exec();

    // Setup a query model to hold the data
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);

    // Convert to a QSortFilterProxyModel
    QSortFilterProxyModel *sortModel = new QSortFilterProxyModel();
    sortModel->setSourceModel(model);

    // Put the model into the table view
    m_ui->TypeTableView->setModel(sortModel);

    // Table style
    m_ui->TypeTableView->resizeColumnToContents(0);
    m_ui->TypeTableView->resizeRowsToContents();

    // Close the database connection
    db->close();
}
