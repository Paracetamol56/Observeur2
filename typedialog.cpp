#include "typedialog.h"
#include "ui_typedialog.h"

TypeDialog::TypeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TypeDialog)
{
    ui->setupUi(this);
}

TypeDialog::~TypeDialog()
{
    delete ui;
}
