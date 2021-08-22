#ifndef INSTRUMENTCALCULATIONSDIALOG_H
#define INSTRUMENTCALCULATIONSDIALOG_H

// Widget
#include <QWidget>

// Debug output
#include <QDebug>

// UI elements
#include <QString>
#include <QStringList>
#include <QStringList>
#include <QTextBrowser>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QItemDelegate>
#include <QDoubleSpinBox>
#include <math.h>

#define PI 3.14159265358979323846264338327950288419716939937510582

// Error handling
#include "errorhandler.h"

// Item delegate to force double spinbox when editing the table
// https://stackoverflow.com/a/22708821
struct Delegate : public QItemDelegate
{
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem & /* unused */, const QModelIndex & /* unused */) const
    {
        QDoubleSpinBox *doubleSpinBox = new QDoubleSpinBox(parent);
        doubleSpinBox->setValue(0.00);
        doubleSpinBox->setMaximum(90.00);
        return doubleSpinBox;
    }
};


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
    void on_addPushButton_clicked();
    void on_removePushButton_clicked();
};

#endif // INSTRUMENTCALCULATIONSDIALOG_H
