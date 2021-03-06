#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>

// Debug output
#include <QDebug>

// Error handling
#include "errorhandler.h"

#include <QFile>
#include <QFileDialog>
#include <QSettings>
#include "mainwindow.h"
#include "angleutilities/angle.h"
#include "errorhandler.h"

namespace Ui
{
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::SettingDialog *m_ui;
    QWidget *parentWidget;

public:
    explicit SettingDialog(QWidget *parent = nullptr);
    ~SettingDialog();

private slots:
    void on_SavePushButton_clicked();
    void on_CancelPushButton_clicked();
    void on_DBBrowsePushButton_clicked();

signals:
    void saveState();
};

#endif // SETTINGDIALOG_H
