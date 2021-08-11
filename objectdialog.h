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

namespace Ui {
class ObjectDialog;
}

class ObjectDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::ObjectDialog *m_ui = nullptr;
    QSqlDatabase *m_db = nullptr;
    int m_id = 0;

    // Form
    QLineEdit *m_messierEdit = nullptr;
    QLineEdit *m_ngcEdit = nullptr;

public:
    explicit ObjectDialog(QWidget *parent = nullptr, QSqlDatabase *database = nullptr, const unsigned int objectId = 0);
    ~ObjectDialog();
private slots:
    void on_messierPushButton_clicked();
    void on_ngcPushButton_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // OBJECTDIALOG_H
