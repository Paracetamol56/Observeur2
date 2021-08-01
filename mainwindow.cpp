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
    dbPath =  dbPath + QString("/data.sqlite");
    qDebug() << dbPath;
    m_db->setDatabaseName(dbPath);


    // ######### Get data from database to fill the constallation table ########## //

    // Open the database connection
    m_db->open();

    // Query container object
    QSqlQuery query;

    // === Constellation query
    // Set the query
    query.prepare("SELECT `constellation_name` AS `Constellations` FROM `constellations` WHERE 1");
    query.exec();

    // Add items one by one in a list widget
    while(query.next())
    {
        QListWidgetItem* item = new QListWidgetItem;
        QString str = query.value(0).toString();
        m_constellationFilter.push_back(str);
        item->setText(str);
        item->setCheckState(Qt::Checked);
        m_ui->ConstellationListWidget->addItem(item);
    }

    // === Type query
    // Set the query
    query.prepare("SELECT `category_name` AS `Type` FROM `categories` WHERE 1 ORDER BY `Type`");
    query.exec();

    // Add items one by one in a list widget
    while(query.next())
    {
        QListWidgetItem* item = new QListWidgetItem;
        QString str = query.value(0).toString();
        m_typeFilter.push_back(str);
        item->setText(str);
        item->setCheckState(Qt::Checked);
        m_ui->TypeListWidget->addItem(item);
    }

    // Close the database connection
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
/// Object list updater
/// \brief MainWindow::updateObject
///
void MainWindow::updateObject()
{
    // Open the database connection
    m_db->open();

    // Query container object
    QSqlQuery query;

    // === Constellation query
    // Set the query
    QString queryStr =
            "SELECT `object_name` FROM `objects` WHERE 1";

    query.prepare(queryStr);
    query.exec();

    // Add items one by one in a list widget
    while(query.next())
    {

    }

    // Close the database connection
    m_db->close();
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


///
/// \brief MainWindow::on_ConstellationListWidget_itemClicked
/// \param item
///
void MainWindow::on_ConstellationListWidget_itemClicked(QListWidgetItem *item)
{
    // If the clicked item is checked
    if (item->checkState() == Qt::Checked)
    {
        // Verify if the item isn't already in the vector
        if (m_constellationFilter.count(item->text()) < 1)
        {
            // Add the item in the vector
            m_constellationFilter.push_back(item->text());
        }
    }
    // Else
    else if (item->checkState() == Qt::Unchecked)
    {
        // Remove the item from the vector
        m_constellationFilter.removeOne(item->text());
    }
}


///
/// \brief MainWindow::on_SortButton_clicked
///
void MainWindow::on_SortButton_clicked()
{

}


///
/// \brief MainWindow::on_actionLight_triggered
///
void MainWindow::on_actionLight_triggered()
{
    QPalette lightPalette(palette());
    lightPalette.setColor(QPalette::Base, Qt::lightGray);
    setPalette(lightPalette);
}


///
/// \brief MainWindow::on_actionDark_triggered
///
void MainWindow::on_actionDark_triggered()
{
    QPalette darkPalette(palette());
    darkPalette.setColor(QPalette::Base, Qt::darkGray);
    setPalette(darkPalette);
}


///
/// \brief MainWindow::on_actionNight_vision_triggered
///
void MainWindow::on_actionNight_vision_triggered()
{
    QPalette nightVisionPalette(palette());
    // Color palette
    // 207, 12, 0, 255   |   #cf0c00
    // 156, 10, 1, 255   |   #9c0a01
    // 106, 7, 2, 255    |   #6a0702
    // 55, 5, 2, 255     |   #370502
    // 4, 2, 3, 255      |   #040203

    setPalette(nightVisionPalette);
}


///
/// \brief MainWindow::on_AllConstellationCheckBox_clicked
///
void MainWindow::on_AllConstellationCheckBox_clicked()
{
    qDebug() << m_ui->AllConstellationCheckBox->checkState();
    if (m_ui->AllConstellationCheckBox->checkState() == Qt::Checked)
    {
        // Clear old filter vector
        m_constellationFilter.clear();

        // Iterate through the list widget
        for(int i = 0; i < m_ui->ConstellationListWidget->count(); ++i)
        {
            QListWidgetItem* item = m_ui->ConstellationListWidget->item(i);
            item->setCheckState(Qt::Checked);
            m_constellationFilter.push_back(item->text());
        }
    }
    else if (m_ui->AllConstellationCheckBox->checkState() == Qt::Unchecked)
    {
        // Clear old filter vector
        m_constellationFilter.clear();

        // Iterate through the list widget
        for(int i = 0; i < m_ui->ConstellationListWidget->count(); ++i)
        {
            QListWidgetItem* item = m_ui->ConstellationListWidget->item(i);
            item->setCheckState(Qt::Unchecked);
        }
    }
    qDebug() << m_constellationFilter;
}
