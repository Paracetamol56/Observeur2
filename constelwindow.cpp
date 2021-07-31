#include "constelwindow.h"
#include "ui_constelwindow.h"

///
/// Constructor
/// \brief ConstelWindow::ConstelWindow
/// \param parent
///
ConstelWindow::ConstelWindow()
    : m_ui(new ConstelWindow)
    , m_db(new QSqlDatabase)
{
    // ########################## Setup the UI ######################### //

    //m_ui->setupUi(this);


    // ####################### Initiate database ####################### //

    // Set database type
    *m_db = QSqlDatabase::addDatabase("QSQLITE");
    // Set the database path and name
    QString dbPath = QDir::currentPath();
    dbPath =  dbPath + QString("/data.db");
    m_db->setDatabaseName(dbPath);


    // ######### Get data from database to fill the constallation table ########## //

    // Open the database connection
    m_db->open();

    // === Debug code
    //qDebug() << m_db->lastError();

    // Set the query
    QSqlQuery query;
    query.prepare("SELECT `constellation_name` AS `Constellations` FROM `constellation` WHERE 1");
    query.exec();

    // === Debug code
    /*
    while(query.next()){
        QString str = query.value(0).toString();
        qDebug() << qPrintable(str) ;
    }
    */

    // Put the data into a model
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery(query);
    // Display data on the main table view
    //m_ui->ConstellationListView->setModel(model);
    // Close the database connsection
    m_db->close();
}


///
/// Destructor
/// \brief ConstelWindow::~ConstelWindow
///
ConstelWindow::~ConstelWindow()
{
    delete m_ui;
}
