#include "constellationdialog.h"
#include "ui_constellationdialog.h"


///
/// Constructor
/// \brief ConstellationDialog::ConstellationDialog
/// \param parent
/// \param db
///
ConstellationDialog::ConstellationDialog(QWidget *parent, QSqlDatabase *db)
    : QDialog(parent)
    , m_ui(new Ui::ConstellationDialog)
{
    // ########################## Setup the UI ######################### //

    m_ui->setupUi(this);


    // ######### Get data from database to fill the constallation table ########## //

    tablePopulate(db);
}


///
/// Destructor
/// \brief ConstellationDialog::~ConstellationDialog
///
ConstellationDialog::~ConstellationDialog()
{
    delete m_ui;
}


///
/// Table filler function
/// \brief ConstellationDialog::tablePopulate
/// \param db
///
void ConstellationDialog::tablePopulate(QSqlDatabase *db)
{
    // Open the database connection
    db->open();

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
    query.exec();

    // Setup a query model to hold the data
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);

    // Convert to a QSortFilterProxyModel
    QSortFilterProxyModel *sortModel = new QSortFilterProxyModel();
    sortModel->setSourceModel(model);

    // Put the model into the table view
    m_ui->ConstellationTableView->setModel(sortModel);

    // Table style
    m_ui->ConstellationTableView->resizeColumnsToContents();
    m_ui->ConstellationTableView->resizeRowsToContents();

    // Close the database connection
    db->close();
}
