#include "mainwindow.h"
#include "ui_mainwindow.h"

///
/// Constructor
/// \brief MainWindow::MainWindow
/// \param parent
///
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
    , m_db(new QSqlDatabase)
{
    // ########################## Setup the UI ######################### //

    m_ui->setupUi(this);


    // ####################### Initiate database ####################### //

    // Set database type
    *m_db = QSqlDatabase::addDatabase("QSQLITE");
    // Set the database path and name
    QString dbPath = QDir::currentPath();
    dbPath =  dbPath + QString("/data.db");
    m_db->setDatabaseName(dbPath);


    // ######### Get data from database to fill the tableView ########## //

    // Open the database connection
    m_db->open();

    // === Debug code
    //qDebug() << m_db->lastError();

    // Set the query
    QSqlQuery query;
    query.prepare("SELECT * FROM constellation WHERE 1");
    query.exec();

    // === Debug code
    /*
    while(query.next()){
        QString str = query.value(1).toString();
        qDebug() << qPrintable(str) ;
    }
    */

    // Put the data into a model
    QSqlQueryModel* model = new QSqlQueryModel;
    model->setQuery(query);
    // Display data on the main table view
    m_ui->ConstellationTableView->setModel(model);
    // Close the database connsection
    m_db->close();
}


///
/// Destructor
/// \brief MainWindow::~MainWindow
///
MainWindow::~MainWindow()
{
    delete m_ui;
}


///
/// Quit is triggered
/// \brief MainWindow::on_actionQuitter_triggered
///
void MainWindow::on_actionQuitter_triggered()
{
    QApplication::quit();
}


///
/// About is triggered
/// \brief MainWindow::on_actionA_propos_triggered
///
void MainWindow::on_actionA_propos_triggered()
{
    QMessageBox aboutMessageBox;
    aboutMessageBox.setText("A propos de l'Observeur 2");
    aboutMessageBox.setInformativeText("Logiciel de catalogue d'objet personnalisé pour l'astronomie amateur");
    aboutMessageBox.setStandardButtons(QMessageBox::Ok);
    aboutMessageBox.setIcon(QMessageBox::Information);
    aboutMessageBox.exec();
}
