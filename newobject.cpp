#include "newobject.h"
#include "ui_newobject.h"

NewObject::NewObject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewObject)
{
    ui->setupUi(this);
}

NewObject::~NewObject()
{
    delete ui;
}
