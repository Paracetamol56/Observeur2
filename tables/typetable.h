#ifndef TYPETABLE_H
#define TYPETABLE_H

#include "tabledialog.h"

// Error handling
#include "errorhandler.h"

class TypeTable
    : public TableDialog
{

public:

    TypeTable(QWidget *parent = nullptr, QSqlDatabase *db = nullptr);

    void tablePopulate() override;
};

#endif // TYPETABLE_H
