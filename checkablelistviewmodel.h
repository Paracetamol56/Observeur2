#ifndef CHECKABLELISTVIEWMODEL_H
#define CHECKABLELISTVIEWMODEL_H

#include <QSqlQueryModel>
#include <QSet>
#include <QColor>

class CheckableListViewModel : public QSqlQueryModel
{
private:
    // ###################### Private attributes ####################### //
    QSet<QPersistentModelIndex> checkedItems;

public:
    // ######################## Public methods ######################### //

    // Constructor
    CheckableListViewModel(QObject* parent = 0);
    CheckableListViewModel(const QStringList & strings, QObject* parent = 0);
    // Destructor
    ~CheckableListViewModel();

    Qt::ItemFlags flags(const QModelIndex& index) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role);
    void save();
};

#endif // CHECKABLELISTVIEWMODEL_H
