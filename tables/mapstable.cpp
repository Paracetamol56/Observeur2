#include "mapstable.h"
#include "ui_mapstable.h"

MapsTable::MapsTable(QWidget *parent, QSqlDatabase *db)
    : QWidget(parent)
    , ui(new Ui::mapsTable)
    , m_db(db)
{
    ui->setupUi(this);
}

MapsTable::~MapsTable()
{
    delete ui;
}
