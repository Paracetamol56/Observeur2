#ifndef MAPSTABLE_H
#define MAPSTABLE_H

#include <QWidget>

namespace Ui {
class mapsTable;
}

class mapsTable : public QWidget
{
    Q_OBJECT

public:
    explicit mapsTable(QWidget *parent = nullptr);
    ~mapsTable();

private:
    Ui::mapsTable *ui;
};

#endif // MAPSTABLE_H
