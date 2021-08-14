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
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QTextBrowser>
#include <QtCharts>

#include "angleutilities/angle.h"
#include "angleutilities/equatorialposition.h"
#include "objectform.h"
#include "mainwindow.h"

namespace Ui {
class ObjectDialog;
}

class ObjectDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::ObjectDialog *m_ui = nullptr;
    QSqlDatabase *m_db = nullptr;

    // Object values
    int m_id = 0;
    Angle m_rightAscension;
    Angle m_declination;

    // Form
    QLineEdit *m_messierEdit = nullptr;
    QLineEdit *m_ngcEdit = nullptr;

    // Graph
    QtCharts::QChartView *m_chartView = nullptr;
    QtCharts::QChart *m_chart = nullptr;

public:
    explicit ObjectDialog(QWidget *parent = nullptr, QSqlDatabase *database = nullptr, const unsigned int objectId = 0);
    ~ObjectDialog();

    void computeGraph();

private slots:
    void on_messierPushButton_clicked();
    void on_ngcPushButton_clicked();
    void on_ModifyPushButton_clicked();
    void on_CloseushButton_clicked();
};

#endif // OBJECTDIALOG_H
