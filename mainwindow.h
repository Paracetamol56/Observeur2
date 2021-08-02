#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Window
#include <QMainWindow>

// SQL Database
#include <QSqlDatabase>
#include <QSql>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>

// Files access
#include <QDir>
#include <QFile>

// Debug output
#include <QDebug>

// UI elements
#include <QString>
#include <QVector>
#include <QMessageBox>
#include <QListView>
#include <QListWidgetItem>

// Other windows
#include <constellationdialog.h>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    // ###################### Private attributes ####################### //

    // UI object
    Ui::MainWindow* m_ui;
    // Database object
    QSqlDatabase* m_db;

    // Filters
    // Constellation filter
    QVector<QString> m_constellationFilter = {};
    // Periode filter
    QVector<QString> m_periodeFilter = {};
    // Type filter
    QVector<QString> m_typeFilter = {};

public:
    // ######################## Public methods ######################### //

    // Constructor
    explicit MainWindow(QWidget* parent = 0);
    // Destructor
    ~MainWindow();

    // Object list updater
    void updateObject();

    // ######################### Private slots ######################### //
private slots:
    void on_actionA_propos_triggered();
    void on_actionQuitter_triggered();
    void on_AllConsellationsButton_clicked();
    void on_ConstellationListWidget_itemClicked(QListWidgetItem *item);
    void on_SortButton_clicked();
    void on_actionLight_triggered();
    void on_actionDark_triggered();
    void on_actionNight_vision_triggered();
    void on_AllConstellationCheckBox_clicked();
    void on_AllTypeCheckBox_clicked();
};

#endif // MAINWINDOW_H
