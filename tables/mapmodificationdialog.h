#ifndef MAPMODIFICATIONDIALOG_H
#define MAPMODIFICATIONDIALOG_H

// Dialog
#include <QDialog>

// SQL Database
#include <QSqlDatabase>
#include <QSql>
#include <QSqlError>
#include <QSqlQuery>

// Debug output
#include <QDebug>

// Error handling
#include "errorhandler.h"

// UI elements
#include <QString>

namespace Ui {
class MapModificationDialog;
}

class MapModificationDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::MapModificationDialog *m_ui;
    QSqlDatabase *m_db;
    const unsigned int m_idToModify;
    const QString m_tableString;

public:
    explicit MapModificationDialog(QWidget *parent = nullptr, QSqlDatabase *db = nullptr, const unsigned int table = 0, const unsigned int id = 0);
    ~MapModificationDialog();

private slots:
    void on_SavePushButton_clicked();
    void on_CancelPushButton_clicked();
};

#endif // MAPMODIFICATIONDIALOG_H
