#ifndef OBJECTTABLE_H
#define OBJECTTABLE_H

#include "tabledialog.h"

class ObjectTable
    : public TableDialog
{
public:

    ObjectTable(QWidget *parent = nullptr, QSqlDatabase *db = nullptr);

    void tablePopulate() override;
};

#endif // OBJECTTABLE_H
