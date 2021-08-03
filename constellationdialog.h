#ifndef CONSTELLATIONDIALOG_H
#define CONSTELLATIONDIALOG_H

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

// UI elements



namespace Ui {
class ConstellationDialog;
}

class ConstellationDialog : public QDialog
{
    Q_OBJECT

private:
    // ###################### Private attributes ####################### //

    Ui::ConstellationDialog *m_ui;

public:
    // ######################## Public methods ######################### //

    //Constructor
    explicit ConstellationDialog(QWidget *parent = nullptr, QSqlDatabase *db = nullptr);
    // Destructor
    ~ConstellationDialog();

    // Table populate function
    void tablePopulate(QSqlDatabase *db);
};

#endif // CONSTELLATIONDIALOG_H
