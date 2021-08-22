#include "instrumentcalculationsdialog.h"
#include "ui_instrumentcalculationsdialog.h"


InstrumentCalculationsDialog::InstrumentCalculationsDialog(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::InstrumentCalculationsDialog)
{
    m_ui->setupUi(this);
}


InstrumentCalculationsDialog::~InstrumentCalculationsDialog()
{
    delete m_ui;
}
