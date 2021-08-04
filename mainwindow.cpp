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
    // Check if file exists
    if (QFile::exists(dbPath))
    {
        // qDebug() << dbPath;
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

        // Display all the objects
        updateObject();
    }
    else
    {
        // Display a message box if the database file is not found
        QMessageBox errorMessageBox;
        errorMessageBox.setText("Erreur : Base de donnée manquante");
        errorMessageBox.setInformativeText("Aucun fichier \"data.sqlite\" trouvé");
        errorMessageBox.setStandardButtons(QMessageBox::Ok);
        errorMessageBox.setIcon(QMessageBox::Critical);
        errorMessageBox.exec();
    }
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
    // Format constellation filter
    QString constellationFilterString = "";
    QVectorIterator<QString> it(m_constellationFilter);
    while (it.hasNext()) {
        constellationFilterString += ("'" + it.next() + "', ");
    }
    int lastIndex = constellationFilterString.lastIndexOf(QChar(','));
    constellationFilterString = constellationFilterString.left(lastIndex);
    qDebug() << constellationFilterString;


    // Open the database connection
    m_db->open();

    // Query container object
    QSqlQuery query;

    // === Constellation query
    // Set the query
    query.prepare(
                "SELECT "
                "objects.`object_name` AS `Nom`, "
                "objects.`object_messier` AS `M`, "
                "objects.`object_ngc` AS `NGC`, "
                "categories.`category_name` AS `Category`, "
                "constellations.`constellation_name` AS `Constellation`, "
                "objects.`object_apparent_magnitude` AS `Magnitude apparente`, "
                "objects.`object_appreciation` AS `Appreciation`, "
                "objects.`object_note` AS `Note /10`, "
                "skymap1.`skymap1_number` AS `Carte (N1)`, "
                "skymap2.`skymap2_number` AS `Carte (N2)`, "
                "skymap3.`skymap3_number` AS `Carte (N3)` "
                "FROM objects "
                "INNER JOIN categories "
                "ON categories.`category_id` = objects.`object_category` "
                "INNER JOIN constellations "
                "ON constellations.`constellation_id` = objects.`object_constellation` "
                "INNER JOIN skymap1 "
                "ON skymap1.`skymap1_id` = objects.`object_skymap1_id` "
                "INNER JOIN skymap2 "
                "ON skymap2.`skymap2_id` = objects.`object_skymap2_id` "
                "INNER JOIN skymap3 "
                "ON skymap3.`skymap3_id` = objects.`object_skymap3_id` "
                "WHERE constellations.`constellation_name` IN ("+ constellationFilterString + ") "
                "ORDER BY objects.`object_name` ASC;"
                );

    query.exec();

    // Setup a query model to hold the data
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);

    // Convert to a QSortFilterProxyModel
    QSortFilterProxyModel *sortModel = new QSortFilterProxyModel();
    sortModel->setSourceModel(model);

    // Put the model into the table view
    m_ui->objectTableView->setModel(sortModel);

    // Table style
    m_ui->objectTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_ui->objectTableView->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Stretch);
    m_ui->objectTableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

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
    ConstellationDialog dialog(nullptr, m_db);
    dialog.setModal(true);
    dialog.exec();
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

            // If all items are checked (filter count == list count)
            if (m_constellationFilter.count() == m_ui->ConstellationListWidget->count())
            {
                // Checked the parent checkbox
                m_ui->AllConstellationCheckBox->setCheckState(Qt::Checked);
            }
            // Else
            else
            {
                // Partialy check the parent checkbox
                m_ui->AllConstellationCheckBox->setCheckState(Qt::PartiallyChecked);
            }
        }
    }
    // Else
    else if (item->checkState() == Qt::Unchecked)
    {
        // Remove the item from the vector
        m_constellationFilter.removeOne(item->text());

        if (m_constellationFilter.count() < 1)
        {
            m_ui->AllConstellationCheckBox->setCheckState(Qt::Unchecked);
        }
        else
        {
            m_ui->AllConstellationCheckBox->setCheckState(Qt::PartiallyChecked);
        }
    }
    // Update the object table
    updateObject();
}


///
/// \brief MainWindow::on_AllConstellationCheckBox_clicked
///
void MainWindow::on_AllConstellationCheckBox_clicked()
{
    // If AllConstellationCheckBox is checked
    if (m_ui->AllConstellationCheckBox->checkState() == Qt::Checked)
    {
        // Clear old filter vector
        m_constellationFilter.clear();

        // Iterate through the list widget
        for(int i = 0; i < m_ui->ConstellationListWidget->count(); ++i)
        {
            // Set the item checked
            QListWidgetItem* item = m_ui->ConstellationListWidget->item(i);
            item->setCheckState(Qt::Checked);
            // Add the item to the table
            m_constellationFilter.push_back(item->text());
        }
    }
    // Else
    else if (m_ui->AllConstellationCheckBox->checkState() == Qt::Unchecked)
    {
        // Clear old filter vector
        m_constellationFilter.clear();

        // Iterate through the list widget
        for(int i = 0; i < m_ui->ConstellationListWidget->count(); ++i)
        {
            // Set the item unchecked
            QListWidgetItem* item = m_ui->ConstellationListWidget->item(i);
            item->setCheckState(Qt::Unchecked);
        }
    }
    // Update the object table
    updateObject();
}


///
/// \brief MainWindow::on_AllTypesButton_clicked
///
void MainWindow::on_AllTypesButton_clicked()
{
    TypeDialog dialog(nullptr, m_db);
    dialog.setModal(true);
    dialog.exec();
}


///
/// \brief MainWindow::on_TypeListWidget_itemClicked
/// \param item
///
void MainWindow::on_TypeListWidget_itemClicked(QListWidgetItem *item)
{
    // If the clicked item is checked
    if (item->checkState() == Qt::Checked)
    {
        // Verify if the item isn't already in the vector
        if (m_typeFilter.count(item->text()) < 1)
        {
            // Add the item in the vector
            m_typeFilter.push_back(item->text());

            // If all items are checked (filter count == list count)
            if (m_typeFilter.count() == m_ui->TypeListWidget->count())
            {
                // Checked the parent checkbox
                m_ui->AllTypeCheckBox->setCheckState(Qt::Checked);
            }
            // Else
            else
            {
                // Partialy check the parent checkbox
                m_ui->AllTypeCheckBox->setCheckState(Qt::PartiallyChecked);
            }
        }
    }
    // Else
    else if (item->checkState() == Qt::Unchecked)
    {
        // Remove the item from the vector
        m_typeFilter.removeOne(item->text());

        if (m_typeFilter.count() < 1)
        {
            m_ui->AllTypeCheckBox->setCheckState(Qt::Unchecked);
        }
        else
        {
            m_ui->AllTypeCheckBox->setCheckState(Qt::PartiallyChecked);
        }
    }
    // Update the object table
    updateObject();
}


///
/// \brief MainWindow::on_AllTypeCheckBox_clicked
///
void MainWindow::on_AllTypeCheckBox_clicked()
{
    // If AllConstellationCheckBox is checked
    if (m_ui->AllTypeCheckBox->checkState() == Qt::Checked)
    {
        // Clear old filter vector
        m_typeFilter.clear();

        // Iterate through the list widget
        for(int i = 0; i < m_ui->TypeListWidget->count(); ++i)
        {
            // Set the item checked
            QListWidgetItem* item = m_ui->TypeListWidget->item(i);
            item->setCheckState(Qt::Checked);
            // Add the item to the table
            m_typeFilter.push_back(item->text());
        }
    }
    // Else
    else if (m_ui->AllTypeCheckBox->checkState() == Qt::Unchecked)
    {
        // Clear old filter vector
        m_typeFilter.clear();

        // Iterate through the list widget
        for(int i = 0; i < m_ui->TypeListWidget->count(); ++i)
        {
            // Set the item unchecked
            QListWidgetItem* item = m_ui->TypeListWidget->item(i);
            item->setCheckState(Qt::Unchecked);
        }
    }
    // Update the object table
    updateObject();
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
