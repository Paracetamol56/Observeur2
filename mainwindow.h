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
#include "constellationtable.h"
#include "typetable.h"
#include "objecttable.h"
#include "objectform.h"

// Error handling
#include "errorhandler.h"


namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    Ui::MainWindow *m_ui = nullptr;
    QSqlDatabase *m_db = nullptr;
    QVector<unsigned int> m_selectedId = {};

    // Filters
    // Constellation filter
    QVector<QString> m_constellationFilter = {};
    // Periode filter
    QVector<QString> m_periodeFilter = {};
    // Type filter
    QVector<QString> m_typeFilter = {};

public:

    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

    void updateObject();
    void tableSelectionChanged();

private slots:

    void on_actionA_propos_triggered();
    void on_actionQuitter_triggered();
    void on_AllConsellationsButton_clicked();
    void on_ConstellationListWidget_itemClicked(QListWidgetItem *item);
    void on_actionLight_triggered();
    void on_actionDark_triggered();
    void on_actionNight_vision_triggered();
    void on_AllConstellationCheckBox_clicked();
    void on_AllTypeCheckBox_clicked();
    void on_TypeListWidget_itemClicked(QListWidgetItem *item);
    void on_AllTypesButton_clicked();
    void on_actionNouvel_objet_triggered();
    void on_AllObjectsPushButton_clicked();
    void on_objectTableView_customContextMenuRequested(const QPoint &pos);
    void on_actionAfficher_toute_les_constellations_triggered();
    void on_actionAfficher_tous_les_types_triggered();
    void on_actionAfficher_tous_les_objets_triggered();
    void on_actionAfficher_la_todo_list_triggered();
    void on_actionModifier_un_objet_triggered();
    void on_actionSupprimer_un_objet_triggered();
};

#endif // MAINWINDOW_H
