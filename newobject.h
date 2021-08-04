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

    // Input values
    QString *m_name = nullptr;
    int *m_messier = nullptr;
    int *m_ngc = nullptr;
    QString *m_otherName1 = nullptr;
    QString *m_otherName2 = nullptr;
    QString *m_category = nullptr;
    QString *m_constellation = nullptr;
    double *m_apparentMagnitude = nullptr;
    QString *m_rightAscension = nullptr;
    QString *m_declination = nullptr;
    int *m_note = nullptr;
    int *m_skyMap1 = nullptr;
    int *m_skyMap2 = nullptr;
    int *m_skyMap3 = nullptr;
    double *m_distance = nullptr;
    double *m_diameter = nullptr;

public:
    // ######################## Public methods ######################### //

    //Constructor
    explicit NewObject(QWidget *parent = nullptr, QSqlDatabase *db = nullptr);
    // Destructor
    ~NewObject();

private slots:
    void on_horizontalSlider_valueChanged(int value);
};

#endif // NEWOBJECT_H
