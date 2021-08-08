#include "constellationtable.h"
#include "ui_tabledialog.h"


///
/// Constructor
/// \brief ConstellationTable::ConstellationTable
/// \param parent
/// \param database
///
ConstellationTable::ConstellationTable(QWidget *parent, QSqlDatabase *database)
    : TableDialog(parent, database)
{
    tablePopulate();
}


///
/// Table populate function
/// \brief ConstellationTable::tablePopulate
///
void ConstellationTable::tablePopulate()
{
    // Open the database connection
    m_db->open();

    // Query container object
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
        Error sqlError(ErrorPriority::Warning, &query);
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
    setWindowTitle("Constellation");
    m_ui->label->setText("Toutes les constellations");

    // Table style
    m_ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // Close the database connection
    m_db->close();
}
