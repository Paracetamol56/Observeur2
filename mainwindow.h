#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSqlDatabase>
#include <QSql>
#include <QSqlError>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>
#include <QVector>
#include <QMessageBox>
#include <QListView>

namespace Ui {
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

public:
    // ######################## Public methods ######################### //

    // Constructor
    explicit MainWindow(QWidget* parent = 0);
    // Destructor
    ~MainWindow();
private slots:
    void on_actionA_propos_triggered();
    void on_actionQuitter_triggered();
};

#endif // MAINWINDOW_H
