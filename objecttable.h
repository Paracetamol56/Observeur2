#ifndef OBJECTTABLE_H
#define OBJECTTABLE_H

#include "tabledialog.h"

// Error handling
#include "errorhandler.h"

class ObjectTable
    : public TableDialog
{

public:
    // ######################## Public methods ######################### //

    // Constructor
    ObjectTable(QWidget *parent = nullptr, QSqlDatabase *db = nullptr);

    // Table populate function
    void tablePopulate() override;
};

#endif // OBJECTTABLE_H
