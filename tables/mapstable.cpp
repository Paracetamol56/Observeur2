#include "mapstable.h"
#include "ui_mapstable.h"

mapsTable::mapsTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mapsTable)
{
    ui->setupUi(this);
}

mapsTable::~mapsTable()
{
    delete ui;
}
