#ifndef NEWOBJECT_H
#define NEWOBJECT_H

// Widget
#include <QWidget>

// SQL Database
#include <QSqlDatabase>
#include <QSql>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>

// Debug output
#include <QDebug>

// UI elements

namespace Ui
{
class NewObject;
}

class NewObject : public QWidget
{
    Q_OBJECT

private:
    // ###################### Private attributes ####################### //

    Ui::NewObject *m_ui;
    QSqlDatabase *m_db;

public:
    // ######################## Public methods ######################### //

    //Constructor
    explicit NewObject(QWidget *parent = nullptr, QSqlDatabase *db = nullptr);
    // Destructor
    ~NewObject();
};

#endif // NEWOBJECT_H
