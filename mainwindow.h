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
#include <constelwindow.h>

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

    // ######################### Private slots ######################### //
private slots:
    void on_actionA_propos_triggered();
    void on_actionQuitter_triggered();
    void on_AllConsellationsButton_clicked();
    void on_ConstellationListWidget_itemClicked(QListWidgetItem *item);
};

#endif // MAINWINDOW_H
