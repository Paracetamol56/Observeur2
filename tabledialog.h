#ifndef TABLEDIALOG_H
#define TABLEDIALOG_H

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
class TableDialog;
}

class TableDialog
    : public QDialog
{
    Q_OBJECT

protected:
    // ###################### Protected attributes ##################### //

    Ui::TableDialog *m_ui;
    QSqlDatabase *m_db;

public:
    // ######################## Public methods ######################### //

    //Constructor
    explicit TableDialog(QWidget *parent = nullptr, QSqlDatabase *db = nullptr);
    // Destructor
    ~TableDialog();

    // Table populate function
    virtual void tablePopulate() =0;

private slots:

    void on_ClosePushButton_clicked();
    void on_PrintPushButton_clicked();
};

#endif // TABLEDIALOG_H
