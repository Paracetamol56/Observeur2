#ifndef CONSTELWINDOW_H
#define CONSTELWINDOW_H

// Widget
#include <QWidget>

// SQL Database
#include <QSqlDatabase>
#include <QSql>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>

// Files access
#include <QDir>
#include <QFile>

// Debug output
#include <QDebug>

// UI elements
#include <QString>
#include <QVector>
#include <QMessageBox>
#include <QListView>

class ConstelWindow : public QWidget
{
    Q_OBJECT

private:
    // ###################### Private attributes ####################### //

    // UI object
    ConstelWindow* m_ui;
    // Database object
    QSqlDatabase* m_db;

public:
    // ######################## Public methods ######################### //

    // Constructor
    explicit ConstelWindow();
    // Destructor
    ~ConstelWindow();

    // ######################### Private slots ######################### //
private slots:

};

#endif // CONSTELWINDOW_H
