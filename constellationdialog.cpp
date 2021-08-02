#include "constellationdialog.h"
#include "ui_constellationdialog.h"

ConstellationDialog::ConstellationDialog(QWidget *parent, QSqlDatabase *db) :
    QDialog(parent),
    m_ui(new Ui::ConstellationDialog)
{
    // ########################## Setup the UI ######################### //

    m_ui->setupUi(this);


    // ######### Get data from database to fill the constallation table ########## //

    tablePopulate(db);

}

ConstellationDialog::~ConstellationDialog()
{
    delete m_ui;
}

void ConstellationDialog::tablePopulate(QSqlDatabase *db)
{
    // Open the database connection
    db->open();

    // Query container object
    QSqlQuery query;

    // Set the query
    query.prepare("SELECT * FROM `constellations` WHERE 1");
    query.exec();

    // Setup a query model to hold the data
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);

    // Put the model into the table view
    m_ui->ConstellationTableView->setModel(model);

    // Close the database connection
    db->close();
}
