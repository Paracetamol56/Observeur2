#ifndef OBJECTDIALOG_H
#define OBJECTDIALOG_H

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
#include <QDesktopServices>

namespace Ui {
class ObjectDialog;
}

class ObjectDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::ObjectDialog *m_ui = nullptr;
    QSqlDatabase *m_db = nullptr;
    int m_id = 0;

public:
    explicit ObjectDialog(QWidget *parent = nullptr, QSqlDatabase *database = nullptr, const unsigned int objectId = 0);
    ~ObjectDialog();
private slots:
    void on_messierPushButton_clicked();
    void on_ngcPushButton_clicked();
};

#endif // OBJECTDIALOG_H
