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
#include <QString>
#include <QStringList>


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
    // General section
    QString m_name = "";
    int m_messier = 0;
    int m_ngc = 0;
    QString m_otherName1 = "";
    QString m_otherName2 = "";
    QString m_category = "";
    QString m_constellation = "";
    double m_apparentMagnitude = 0.00;
    double m_secondApparentMagnitude = 0.00;
    double m_distance = 0.00;
    double m_diameter = 0.00;

    // Position section
    QString m_rightAscension = "";
    QString m_declination = "";

    // Skymap section
    int m_skyMap1 = 0;
    int m_skyMap2 = 0;
    int m_skyMap3 = 0;

    // Appreciation section
    QString m_description = "";
    int m_note = 0;


public:
    // ######################## Public methods ######################### //

    //Constructor
    explicit NewObject(QWidget *parent = nullptr, QSqlDatabase *db = nullptr);
    // Destructor
    ~NewObject();

    // Verifying function
    bool CheckInput();
    // Insert row function
    void InsertRow();

private slots:

    void on_NoteHorizontalSlider_valueChanged(int value);
    void on_CancelPushButton_clicked();
    void on_SavePushButton_clicked();
    void on_OtherNameLineEdit_1_editingFinished();
    void on_TypeComboBox_currentTextChanged(const QString &arg1);
};

#endif // NEWOBJECT_H
