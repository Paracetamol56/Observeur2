#ifndef INSTRUMENTCALCULATIONSDIALOG_H
#define INSTRUMENTCALCULATIONSDIALOG_H

// Widget
#include <QWidget>

// Debug output
#include <QDebug>

// UI elements
#include <QString>
#include <QStringList>
#include <QTextBrowser>
#include <QDialogButtonBox>
#include <math.h>

#define PI 3.14159265358979323846264338327950288419716939937510582

// Error handling
#include "errorhandler.h"

namespace Ui
{
class InstrumentCalculationsDialog;
}

class InstrumentCalculationsDialog : public QWidget
{
    Q_OBJECT

private:
    Ui::InstrumentCalculationsDialog *m_ui;
    bool checkInput();

public:
    explicit InstrumentCalculationsDialog(QWidget *parent = nullptr);
    ~InstrumentCalculationsDialog();

private slots:
    void on_computePushButton_clicked();
};

#endif // INSTRUMENTCALCULATIONSDIALOG_H
