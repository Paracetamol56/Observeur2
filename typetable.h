#ifndef TYPETABLE_H
#define TYPETABLE_H

#include "tabledialog.h"

class TypeTable
    : public TableDialog
{

public:
    // ######################## Public methods ######################### //

    // Constructor
    TypeTable(QWidget *parent = nullptr, QSqlDatabase *db = nullptr);

    // Table populate function
    void tablePopulate() override;
};

#endif // TYPETABLE_H
