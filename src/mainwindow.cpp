/**
 * Created on Tue Jul 31 2021
 *
 * Copyright (c) 2021 - Mathéo G - All Right Reserved
 *
 * Licensed under the Apache License, Version 2.0
 * Available on GitHub at https://github.com/Paracetamol56/Observeur2 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_ui(new Ui::MainWindow), m_db(new QSqlDatabase)
{
    m_ui->setupUi(this);

    QSettings settings;

    if (settings.contains("theme"))
    {
        if (settings.value("theme").toString() == "dark")
        {
            on_actionDark_triggered();
        }
        else if (settings.value("theme").toString() == "light")
        {
            on_actionLight_triggered();
        }
        else if (settings.value("theme").toString() == "red")
        {
            on_actionNight_vision_triggered();
        }
    }
    else
    {
        SettingDialog settingDialog(nullptr);
        settingDialog.exec();
    }

    QString dbPath = "";
    if (settings.contains("database"))
    {
        dbPath = settings.value("database").toString();
    }
    else
    {
        SettingDialog settingDialog(nullptr);
        settingDialog.exec();
    }

    // Initiate database

    *m_db = QSqlDatabase::addDatabase("QSQLITE");
    // Check if file exists
    if (QFile::exists(dbPath))
    {
        m_db->setDatabaseName(dbPath);

        // Get data from database to fill the constallation table

        m_db->open();

        QSqlQuery query;

        // === Constellation query
        // Set the query
        query.prepare("SELECT `constellation_name` AS `Constellations` FROM `constellations` WHERE 1");

        if (query.exec() == false)
        {
            SqlError sqlError(ErrorPriority::Critical, "Impossible de selectionner les constellations", &query);
            sqlError.printMessage();
        }

        // Add items one by one in a list widget
        while (query.next())
        {
            QListWidgetItem *item = new QListWidgetItem;
            QString str = query.value(0).toString();
            m_constellationFilter.push_back(str);
            item->setText(str);
            item->setCheckState(Qt::Checked);
            m_ui->ConstellationListWidget->addItem(item);
        }

        // === Type query
        // Set the query
        query.prepare("SELECT `category_name` AS `Type` FROM `categories` WHERE 1 ORDER BY `Type`");

        if (query.exec() == false)
        {
            SqlError sqlError(ErrorPriority::Critical, "Impossible de selectionner les types", &query);
            sqlError.printMessage();
        }

        // Add items one by one in a list widget
        while (query.next())
        {
            QListWidgetItem *item = new QListWidgetItem;
            QString str = query.value(0).toString();
            m_typeFilter.push_back(str);
            item->setText(str);
            item->setCheckState(Qt::Checked);
            m_ui->TypeListWidget->addItem(item);
        }

        m_db->close();

        // Display all the objects
        updateObject();

        // Initiate selection
        tableSelectionChanged();
    }
    else
    {
        // Display a message box if the database file is not found
        MissingFileError errorMessage(ErrorPriority::Critical, "Aucun fichier \"data.sqlite\" trouvé", new QFile(dbPath));
        errorMessage.printMessage();
    }

    // Connections
    connect(m_ui->objectTableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::tableSelectionChanged);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

// Object list updater
void MainWindow::updateObject()
{
    // Format constellation filter
    QString constellationFilterString = "";
    {
        QVectorIterator<QString> it(m_constellationFilter);
        while (it.hasNext())
        {
            constellationFilterString += ("'" + it.next() + "', ");
        }
        int lastIndex = constellationFilterString.lastIndexOf(QChar(','));
        constellationFilterString = constellationFilterString.left(lastIndex);
    }

    // Format type filter
    QString typeFilterString = "";
    {
        QVectorIterator<QString> it(m_typeFilter);
        while (it.hasNext())
        {
            typeFilterString += ("'" + it.next() + "', ");
        }
        int lastIndex = typeFilterString.lastIndexOf(QChar(','));
        typeFilterString = typeFilterString.left(lastIndex);
    }

    m_db->open();

    QSqlQuery query;

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
        "WHERE constellations.`constellation_name` IN (" +
        constellationFilterString + ") "
                                    "AND categories.`category_name` IN (" +
        typeFilterString + ")"
                           "ORDER BY objects.`object_name` ASC;");

    if (query.exec() == false)
    {
        SqlError sqlError(ErrorPriority::Critical, "Impossible de selectionner les objets", &query);
        sqlError.printMessage();
    }

    // Setup a query model to hold the data
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);

    QSortFilterProxyModel *sortModel = new QSortFilterProxyModel();
    sortModel->setSourceModel(model);

    // Put the model into the table view
    m_ui->objectTableView->setModel(sortModel);

    // Table style
    m_ui->objectTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_ui->objectTableView->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Stretch);
    m_ui->objectTableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    m_db->close();

    // Clear selection
    m_ui->objectTableView->clearSelection();
    tableSelectionChanged();

    // Reconnect the "selectionChanged" signal
    connect(m_ui->objectTableView->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::tableSelectionChanged);
}

// Is triggered when the object table selection change
void MainWindow::tableSelectionChanged()
{
    QItemSelectionModel *selectionModel = m_ui->objectTableView->selectionModel();

    if (selectionModel->hasSelection())
    {
        QString nameListString = "\"";

        for (int i = 0; i < selectionModel->selectedRows().count(); ++i)
        {
            nameListString += selectionModel->model()->data(selectionModel->selectedRows().at(i).siblingAtColumn(0)).toString();
            nameListString += "\", \"";
        }

        int lastIndex = nameListString.lastIndexOf(QChar(','));
        nameListString = nameListString.left(lastIndex);

        // Get the IDs of selected objects from the database

        m_db->open();

        QSqlQuery query;
        query.prepare(
            "SELECT `object_id`"
            "FROM `objects`"
            "WHERE object_name IN (" +
            nameListString + ")");

        if (query.exec() == false)
        {
            SqlError sqlError(ErrorPriority::Critical, "Impossible de deffinir la selection", &query);
            sqlError.printMessage();
            return;
        }

        m_selectedId.clear();

        while (query.next())
        {
            m_selectedId.push_back(query.value(0).toInt());
        }

        m_db->close();
    }
    else
    {
        m_selectedId = {};
    }

    // Update the menu
    if (m_selectedId.empty())
    {
        m_ui->actionModifier_un_objet->setEnabled(false);               // "Modifier un objet"
        m_ui->actionSupprimer_un_objet->setEnabled(false);              // "Supprimer un objet"
        m_ui->actionAfficher_les_d_tails_de_l_objet->setEnabled(false); // "Afficher les détaills de l'objets"
    }
    else
    {
        if (m_selectedId.count() == 1)
        {
            m_ui->actionModifier_un_objet->setEnabled(true); // "Modifier un objet"
            m_ui->menuEdition->actions().at(2)->setText("Supprimer les objets");
            m_ui->actionSupprimer_un_objet->setEnabled(true);              // "Supprimer les objets"
            m_ui->actionAfficher_les_d_tails_de_l_objet->setEnabled(true); // "Afficher les détaills de l'objets"
        }
        else
        {
            m_ui->actionModifier_un_objet->setEnabled(false); // "Modifier un objet"
            m_ui->menuEdition->actions().at(2)->setText("Supprimer l'objets");
            m_ui->actionSupprimer_un_objet->setEnabled(true);               // "Supprimer un objet"
            m_ui->actionAfficher_les_d_tails_de_l_objet->setEnabled(false); // "Afficher les détaills de l'objets"
        }
    }
}

// BUTTONS EVENTS

void MainWindow::on_AllConsellationsButton_clicked()
{
    ConstellationTable constellationTableDIalog(nullptr, m_db);
    constellationTableDIalog.exec();
}

void MainWindow::on_ConstellationListWidget_itemClicked(QListWidgetItem *item)
{
    // If the clicked item is checked
    if (item->checkState() == Qt::Checked)
    {
        if (m_constellationFilter.count(item->text()) < 1)
        {
            m_constellationFilter.push_back(item->text());

            // If all items are checked (filter count == list count)
            if (m_constellationFilter.count() == m_ui->ConstellationListWidget->count())
            {
                // Checked the parent checkbox
                m_ui->AllConstellationCheckBox->setCheckState(Qt::Checked);
            }
            else
            {
                // Partialy check the parent checkbox
                m_ui->AllConstellationCheckBox->setCheckState(Qt::PartiallyChecked);
            }
        }
    }
    else if (item->checkState() == Qt::Unchecked)
    {
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

    updateObject();
}

void MainWindow::on_AllConstellationCheckBox_clicked()
{
    // If AllConstellationCheckBox is checked
    if (m_ui->AllConstellationCheckBox->checkState() == Qt::Checked)
    {
        m_constellationFilter.clear();

        // Iterate through the list widget
        for (int i = 0; i < m_ui->ConstellationListWidget->count(); ++i)
        {
            // Set the item checked
            QListWidgetItem *item = m_ui->ConstellationListWidget->item(i);
            item->setCheckState(Qt::Checked);
            // Add the item to the table
            m_constellationFilter.push_back(item->text());
        }
    }
    else if (m_ui->AllConstellationCheckBox->checkState() == Qt::Unchecked)
    {
        m_constellationFilter.clear();

        // Iterate through the list widget
        for (int i = 0; i < m_ui->ConstellationListWidget->count(); ++i)
        {
            // Set the item unchecked
            QListWidgetItem *item = m_ui->ConstellationListWidget->item(i);
            item->setCheckState(Qt::Unchecked);
        }
    }

    updateObject();
}

void MainWindow::on_AllTypesButton_clicked()
{
    TypeTable typeTableDialog(nullptr, m_db);
    typeTableDialog.exec();
}

void MainWindow::on_TypeListWidget_itemClicked(QListWidgetItem *item)
{
    // If the clicked item is checked
    if (item->checkState() == Qt::Checked)
    {
        if (m_typeFilter.count(item->text()) < 1)
        {
            m_typeFilter.push_back(item->text());

            // If all items are checked (filter count == list count)
            if (m_typeFilter.count() == m_ui->TypeListWidget->count())
            {
                // Checked the parent checkbox
                m_ui->AllTypeCheckBox->setCheckState(Qt::Checked);
            }
            else
            {
                // Partialy check the parent checkbox
                m_ui->AllTypeCheckBox->setCheckState(Qt::PartiallyChecked);
            }
        }
    }
    else if (item->checkState() == Qt::Unchecked)
    {
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

    updateObject();
}

void MainWindow::on_AllTypeCheckBox_clicked()
{
    // If AllConstellationCheckBox is checked
    if (m_ui->AllTypeCheckBox->checkState() == Qt::Checked)
    {
        m_typeFilter.clear();

        // Iterate through the list widget
        for (int i = 0; i < m_ui->TypeListWidget->count(); ++i)
        {
            // Set the item checked
            QListWidgetItem *item = m_ui->TypeListWidget->item(i);
            item->setCheckState(Qt::Checked);
            // Add the item to the table
            m_typeFilter.push_back(item->text());
        }
    }
    else if (m_ui->AllTypeCheckBox->checkState() == Qt::Unchecked)
    {
        m_typeFilter.clear();

        // Iterate through the list widget
        for (int i = 0; i < m_ui->TypeListWidget->count(); ++i)
        {
            // Set the item unchecked
            QListWidgetItem *item = m_ui->TypeListWidget->item(i);
            item->setCheckState(Qt::Unchecked);
        }
    }

    updateObject();
}

void MainWindow::on_AllObjectsPushButton_clicked()
{
    ObjectTable objectTableDialog(nullptr, m_db);
    objectTableDialog.exec();
}

// MENU EVENTS

void MainWindow::on_actionQuitter_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionParam_tre_triggered()
{
    SettingDialog settingDialog(nullptr);
    settingDialog.exec();
}

void MainWindow::on_actionAide_en_ligne_triggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/Paracetamol56/Observeur2"));
}

void MainWindow::on_actionA_propos_triggered()
{
    QMessageBox aboutMessageBox;
    aboutMessageBox.setText("A propos de l'Observeur 2");
    aboutMessageBox.setInformativeText("Logiciel de catalogue d'objet personnalisé pour l'astronomie amateur");
    aboutMessageBox.setStandardButtons(QMessageBox::Ok);
    aboutMessageBox.setIcon(QMessageBox::Information);
    aboutMessageBox.exec();
}

void MainWindow::on_actionLight_triggered()
{
    QFile qssFile(":/qdarkstyle/light/res/light/light.qss");

    if (qssFile.exists() == false)
    {
        MissingFileError errorMessage(ErrorPriority::Critical, "Le fichier de style est introuvable", &qssFile);
        errorMessage.printMessage();
    }
    else
    {
        QSettings settings;
        settings.setValue("theme", "light");
        qssFile.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&qssFile);
        qApp->setStyleSheet(ts.readAll());
    }
}

void MainWindow::on_actionDark_triggered()
{
    QFile qssFile(":/qdarkstyle/dark/res/dark/dark.qss");

    if (qssFile.exists() == false)
    {
        MissingFileError errorMessage(ErrorPriority::Critical, "Le fichier de style est introuvable", &qssFile);
        errorMessage.printMessage();
    }
    else
    {
        QSettings settings;
        settings.setValue("theme", "dark");
        qssFile.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&qssFile);
        qApp->setStyleSheet(ts.readAll());
    }
}

void MainWindow::on_actionNight_vision_triggered()
{
    QFile qssFile(":/qdarkstyle/red/res/red/red.qss");

    if (qssFile.exists() == false)
    {
        MissingFileError errorMessage(ErrorPriority::Critical, "Le fichier de style est introuvable", &qssFile);
        errorMessage.printMessage();
    }
    else
    {
        QSettings settings;
        settings.setValue("theme", "red");
        qssFile.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&qssFile);
        qApp->setStyleSheet(ts.readAll());
    }
}

void MainWindow::on_actionTout_selectionner_triggered()
{
    m_ui->objectTableView->selectAll();
    tableSelectionChanged();
}

void MainWindow::on_actionNouvel_objet_triggered()
{
    ObjectForm *newObjectWindow = new ObjectForm(this, m_db, 0);
    newObjectWindow->setWindowFlag(Qt::Window);
    connect(newObjectWindow, SIGNAL(newValuesSaved()), this, SLOT(on_newValuesSaved()));
    newObjectWindow->show();
}

void MainWindow::on_actionModifier_un_objet_triggered()
{
    if (m_selectedId.count() == 1)
    {
        ObjectForm *modifyObjectWindow = new ObjectForm(this, m_db, m_selectedId.first());
        modifyObjectWindow->setWindowFlag(Qt::Window);
        connect(modifyObjectWindow, SIGNAL(newValuesSaved()), this, SLOT(on_newValuesSaved()));
        modifyObjectWindow->show();
    }
}

void MainWindow::on_newValuesSaved()
{
    updateObject();
}

void MainWindow::on_actionAfficher_les_d_tails_de_l_objet_triggered()
{
    tableSelectionChanged();
    ObjectDialog objectDialog(this, m_db, m_selectedId.first());
    objectDialog.exec();
}

void MainWindow::on_actionSupprimer_un_objet_triggered()
{
    QMessageBox confirmMessageBox;
    confirmMessageBox.setText("Etes vous sûr de vouloir supprimer cet objet ?");
    confirmMessageBox.setInformativeText("Cette action est irreversible");
    confirmMessageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    confirmMessageBox.setIcon(QMessageBox::Information);
    switch (confirmMessageBox.exec())
    {
    case QMessageBox::Yes:
    {
        tableSelectionChanged();

        QString idToDelete = "\"";
        QVectorIterator<unsigned int> i(m_selectedId);
        while (i.hasNext())
        {
            idToDelete += QString::number(i.next()) += "\", \"";
        }
        idToDelete = idToDelete.left(idToDelete.lastIndexOf(QChar(',')));

        m_db->open();

        QSqlQuery query;
        query.prepare("DELETE FROM `objects` WHERE `object_id` IN (" + idToDelete + ")");
        if (query.exec() == false)
        {
            SqlError sqlError(ErrorPriority::Critical, "Impossible de supprimer le(s) objet(s)", &query);
            sqlError.printMessage();
            return;
        }

        m_db->close();

        updateObject();

        break;
    }
    case QMessageBox::No:
        confirmMessageBox.close();
        break;
    }
}

void MainWindow::on_actionEditer_les_cartes_triggered()
{
    MapsTable *mapsTable = new MapsTable(this, m_db);
    mapsTable->setWindowFlag(Qt::Window);
    mapsTable->show();
}

void MainWindow::on_actionAfficher_toute_les_constellations_triggered()
{
    ConstellationTable constellationTableDIalog(nullptr, m_db);
    constellationTableDIalog.exec();
}

void MainWindow::on_actionAfficher_tous_les_types_triggered()
{
    ConstellationTable constellationTableDIalog(nullptr, m_db);
    constellationTableDIalog.exec();
}

void MainWindow::on_actionAfficher_tous_les_objets_triggered()
{
    ObjectTable objectTableDIalog(nullptr, m_db);
    objectTableDIalog.exec();
}

void MainWindow::on_actionAfficher_la_todo_list_triggered()
{
    // todo
}

void MainWindow::on_actionCalculs_pour_instruments_triggered()
{
    InstrumentCalculationsDialog *instrumentDialog = new InstrumentCalculationsDialog(this);
    instrumentDialog->setWindowFlag(Qt::Window);
    instrumentDialog->show();
}

void MainWindow::on_actionCalculs_solaires_triggered()
{
    SunCalculationsDialog *sunDialog = new SunCalculationsDialog(this);
    sunDialog->setWindowFlag(Qt::Window);
    sunDialog->show();
}

void MainWindow::on_objectTableView_customContextMenuRequested(const QPoint &pos)
{
    QMenu contextMenu;

    // Add object action
    QAction addAction("Ajouter", &contextMenu);
    connect(&addAction, SIGNAL(triggered()), this, SLOT(on_actionNouvel_objet_triggered()));

    // Modification action
    QAction modifyAction("Modifier", &contextMenu);
    connect(&modifyAction, SIGNAL(triggered()), this, SLOT(on_actionModifier_un_objet_triggered()));
    if (m_selectedId.count() != 1)
        modifyAction.setEnabled(false);

    // Show details action
    QAction detailAction("Voir en détail", &contextMenu);
    connect(&detailAction, SIGNAL(triggered()), this, SLOT(on_actionAfficher_les_d_tails_de_l_objet_triggered()));
    if (m_selectedId.count() != 1)
        detailAction.setEnabled(false);

    // Delete object action
    QAction deleteAction("Supprimer", &contextMenu);
    connect(&deleteAction, SIGNAL(triggered()), this, SLOT(on_actionSupprimer_un_objet_triggered()));
    if (m_selectedId.count() < 1)
        deleteAction.setEnabled(false);

    // Select all action
    QAction selectAllAction("Tout selectionner", &contextMenu);
    connect(&selectAllAction, SIGNAL(triggered()), this, SLOT(on_actionTout_selectionner_triggered()));

    // Add to the todo list action
    QAction todoListAction("Ajouter à la todo list", &contextMenu);
    connect(&todoListAction, SIGNAL(triggered()), this, SLOT(/* todo */));
    if (m_selectedId.count() < 1)
        todoListAction.setEnabled(false);

    // Append every actions to the context menu
    contextMenu.addAction(&addAction);
    contextMenu.addAction(&modifyAction);
    contextMenu.addAction(&detailAction);
    contextMenu.addAction(&deleteAction);
    contextMenu.addSeparator();
    contextMenu.addAction(&selectAllAction);
    contextMenu.addAction(&todoListAction);

    contextMenu.exec(m_ui->objectTableView->viewport()->mapToGlobal(pos));
}
