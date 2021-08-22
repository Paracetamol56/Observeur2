#ifndef INSTRUMENTCALCULATIONSDIALOG_H
#define INSTRUMENTCALCULATIONSDIALOG_H

#include <QWidget>

namespace Ui
{
class InstrumentCalculationsDialog;
}

class InstrumentCalculationsDialog : public QWidget
{
    Q_OBJECT

private:
    Ui::InstrumentCalculationsDialog *m_ui;

public:
    explicit InstrumentCalculationsDialog(QWidget *parent = nullptr);
    ~InstrumentCalculationsDialog();
};

#endif // INSTRUMENTCALCULATIONSDIALOG_H
