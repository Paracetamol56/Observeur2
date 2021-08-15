#include "mapstable.h"
#include "ui_mapstable.h"

MapsTable::MapsTable(QWidget *parent, QSqlDatabase *db)
    : QWidget(parent)
    , m_ui(new Ui::mapsTable)
    , m_db(db)
{
    m_ui->setupUi(this);

    // Get skymap data from the database
    try
    {
        m_db->open();

        QSqlQuery query1, query2, query3;

        // === Query 1

        query1.prepare(
                    "SELECT "
                    "`skymap1_number` AS `Numero`, "
                    "`skymap1_right_ascension` AS `Ascension droite`, "
                    "`skymap1_declination` AS `Déclinaison` "
                    "FROM skymap1 "
                    "ORDER BY skymap1.`skymap1_number` + 0 ASC;"
                    );

        if (query1.exec() == false)
        {
            throw SqlError(ErrorPriority::Critical, "Impossible de selectionner les carte 1", &query1);
        }

        // === Query 2

        query2.prepare(
                    "SELECT "
                    "`skymap2_number` AS `Numero`, "
                    "`skymap2_right_ascension` AS `Ascension droite`, "
                    "`skymap2_declination` AS `Déclinaison` "
                    "FROM skymap2 "
                    "ORDER BY skymap2.`skymap2_number` + 0 ASC;"
                    );

        if (query2.exec() == false)
        {
            throw SqlError(ErrorPriority::Critical, "Impossible de selectionner les carte 2", &query1);
        }

        // === Query 3

        query3.prepare(
                    "SELECT "
                    "`skymap3_number` AS `Numero`, "
                    "`skymap3_right_ascension` AS `Ascension droite`, "
                    "`skymap3_declination` AS `Déclinaison` "
                    "FROM skymap3 "
                    "ORDER BY skymap3.`skymap3_number` + 0 ASC;"
                    );

        if (query3.exec() == false)
        {
            throw SqlError(ErrorPriority::Critical, "Impossible de selectionner les carte 3", &query1);
        }

        // Setup query models to hold the data
        QSqlQueryModel *model1 = new QSqlQueryModel();
        model1->setQuery(query1);

        QSqlQueryModel *model2 = new QSqlQueryModel();
        model2->setQuery(query2);

        QSqlQueryModel *model3 = new QSqlQueryModel();
        model3->setQuery(query3);

        // Put the models into table views
        m_ui->tableView->setModel(model1);
        m_ui->tableView_2->setModel(model2);
        m_ui->tableView_3->setModel(model3);

        // Table style
        m_ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        m_ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        m_ui->tableView_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        m_db->close();
    }
    catch (Error &e)
    {
        e.printMessage();
    }
}

MapsTable::~MapsTable()
{
    delete m_ui;
}
