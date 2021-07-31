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


    // ######### Get data from database to fill the constallation table ########## //

    // Open the database connection
    m_db->open();

    // Query container object
    QSqlQuery query;

    // === Constellation query
    // Set the query
    query.prepare("SELECT `constellation_name` AS `Constellations` FROM `constellation` WHERE 1");
    query.exec();

    // Put the data into a model
    QSqlQueryModel* ConstellationModel = new QSqlQueryModel;
    ConstellationModel->setQuery(query);
    // Display data on the main table view
    m_ui->ConstellationListView->setModel(ConstellationModel);

    // === Type query
    // Set the query
    query.prepare("SELECT `category_name` AS `Type` FROM `category` WHERE 1");
    query.exec();

    // Put the data into a model
    QSqlQueryModel* TypeModel = new QSqlQueryModel;
    TypeModel->setQuery(query);
    // Display data on the main table view
    m_ui->TypeListView->setModel(TypeModel);


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
/// \brief MainWindow::on_actionQuitter_triggered
///
void MainWindow::on_actionQuitter_triggered()
{
    QApplication::quit();
}


///
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

///
/// \brief MainWindow::on_AllConsellationsButton_clicked
///
void MainWindow::on_AllConsellationsButton_clicked()
{

}
