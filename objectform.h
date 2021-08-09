#ifndef OBJECTFORM_H
#define OBJECTFORM_H

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

// Error handling
#include "errorhandler.h"

#include "angleutilities.h"


namespace Ui
{
class ObjectForm;
}

class ObjectForm : public QWidget
{
    Q_OBJECT

private:

    Ui::ObjectForm *m_ui;
    QSqlDatabase *m_db;

    int m_objectId = 0;

    // Input values
    // General section
    QString m_name = "";
    int m_messier = 0;
    int m_ngc = 0;
    QString m_otherName1 = "";
    QString m_otherName2 = "";
    int m_category = 0;
    int m_constellation = 0;
    double m_apparentMagnitude = 0.00;
    double m_secondApparentMagnitude = 0.00;
    double m_distance = 0.00;
    double m_diameter = 0.00;

    // Position section
    Angle m_rightAscension = Angle(0.00);
    Angle m_declination = Angle(0.00);

    // Skymap section
    int m_skyMap1 = 0;
    int m_skyMap2 = 0;
    int m_skyMap3 = 0;

    // Appreciation section
    QString m_description = "";
    int m_note = 0;


public:

    explicit ObjectForm(QWidget *parent = nullptr, QSqlDatabase *db = nullptr, int objectId = 0);
    ~ObjectForm();

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

#endif // OBJECTFORM_H
