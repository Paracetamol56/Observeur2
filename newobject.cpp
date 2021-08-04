#include "newobject.h"
#include "ui_newobject.h"

NewObject::NewObject(QWidget *parent, QSqlDatabase *db)
    : QWidget(parent)
    , m_ui(new Ui::NewObject)
    , m_db(db)
{
    m_ui->setupUi(this);
}

NewObject::~NewObject()
{
    delete m_ui;
}
