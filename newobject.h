#ifndef NEWOBJECT_H
#define NEWOBJECT_H

#include <QWidget>

namespace Ui {
class NewObject;
}

class NewObject : public QWidget
{
    Q_OBJECT

public:
    explicit NewObject(QWidget *parent = nullptr);
    ~NewObject();

private:
    Ui::NewObject *ui;
};

#endif // NEWOBJECT_H
