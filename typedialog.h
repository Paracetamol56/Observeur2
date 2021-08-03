#ifndef TYPEDIALOG_H
#define TYPEDIALOG_H

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
class TypeDialog;
}

class TypeDialog : public QDialog
{
    Q_OBJECT

private:
    // ###################### Private attributes ####################### //

    Ui::TypeDialog *m_ui;

public:
    // ######################## Public methods ######################### //

    //Constructor
    explicit TypeDialog(QWidget *parent = nullptr, QSqlDatabase *db = nullptr);
    // Destructor
    ~TypeDialog();

    // Table populate function
    void tablePopulate(QSqlDatabase *db);
};

#endif // TYPEDIALOG_H
