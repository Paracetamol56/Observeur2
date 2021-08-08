#ifndef CONSTELLATIONTABLE_H
#define CONSTELLATIONTABLE_H

#include "tabledialog.h"

// Error handling
#include "errorhandler.h"

class ConstellationTable
    : public TableDialog
{

public:
    // ######################## Public methods ######################### //

    // Constructor
    ConstellationTable(QWidget *parent = nullptr, QSqlDatabase *db = nullptr);

    // Table populate function
    void tablePopulate() override;
};

#endif // CONSTELLATIONTABLE_H
