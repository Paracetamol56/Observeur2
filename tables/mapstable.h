#ifndef MAPSTABLE_H
#define MAPSTABLE_H

// Dialog
#include <QDialog>

// SQL Database
#include <QSqlDatabase>
#include <QSql>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>

// Debug output
#include <QDebug>

// Error handling
#include "errorhandler.h"

// UI elements


namespace Ui {
    class mapsTable;
}

class MapsTable : public QWidget
{
    Q_OBJECT

private:
    Ui::mapsTable *m_ui;

    QSqlDatabase *m_db = nullptr;


public:
    explicit MapsTable(QWidget *parent = nullptr, QSqlDatabase *db = nullptr);
    ~MapsTable();
};

#endif // MAPSTABLE_H
