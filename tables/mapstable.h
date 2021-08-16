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
#include <QString>

#include "angleutilities/angle.h"


namespace Ui {
    class mapsTable;
}

class MapsTable : public QWidget
{
    Q_OBJECT

private:
    Ui::mapsTable *m_ui;

    QSqlDatabase *m_db = nullptr;

    bool checkInput(const unsigned int table = 0, const unsigned int number = 0);
    void updateTable1();
    void updateTable2();
    void updateTable3();
    void resetInputs();

public:
    explicit MapsTable(QWidget *parent = nullptr, QSqlDatabase *db = nullptr);
    ~MapsTable();


private slots:
    void on_quittPushButton_clicked();
    void on_removePushButton_1_clicked();
    void on_removePushButton_2_clicked();
    void on_removePushButton_3_clicked();
    void on_addPushButton_1_clicked();
    void on_addPushButton_2_clicked();
    void on_addPushButton_3_clicked();
};

#endif // MAPSTABLE_H