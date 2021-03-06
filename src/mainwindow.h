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
#include <QSettings>

// Other windows
#include "tables/constellationtable.h"
#include "tables/typetable.h"
#include "tables/objecttable.h"
#include "tables/mapstable.h"
#include "objectform.h"
#include "dialogs/objectdialog.h"
#include "dialogs/settingdialog.h"
#include "dialogs/instrumentcalculationsdialog.h"
#include "dialogs/suncalculationsdialog.h"

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
    bool m_periodeFilter[12] = { true, true, true, true, true, true, true, true, true, true, true };
    // Type filter
    QVector<QString> m_typeFilter = {};

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void databaseInit(QString dbPath);
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
    void on_actionTout_selectionner_triggered();
    void on_actionAfficher_les_d_tails_de_l_objet_triggered();
    void on_actionParam_tre_triggered();
    void on_newValuesSaved();
    void on_actionAide_en_ligne_triggered();
    void on_actionEditer_les_cartes_triggered();
    void on_actionCalculs_pour_instruments_triggered();
    void on_actionCalculs_solaires_triggered();
    void on_UpdatePeriodeButton_clicked();
    void on_AllConstallationCheckBox_clicked();
    void on_AllPeriodesCheckBox_clicked();
    void on_PeriodeListWidget_itemClicked(QListWidgetItem *item);
};

#endif // MAINWINDOW_H
