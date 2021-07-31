#include <checkablelistviewmodel.h>

///
/// \brief CheckableListViewModel::flags
/// \param index
/// \return
///
Qt::ItemFlags CheckableListViewModel::flags (const QModelIndex & index) const
{
    Qt::ItemFlags defaultFlags = QSqlQueryModel::flags(index);
    if (index.isValid()){
        return defaultFlags | Qt::ItemIsUserCheckable;
    }
    return defaultFlags;
}


///
/// \brief CustomListModel::data
/// \param index
/// \param role
/// \return
///
QVariant CheckableListViewModel::data(const QModelIndex &index,
                                 int role) const {
    if (!index.isValid())
        return QVariant();

    if(role == Qt::CheckStateRole)
        return checkedItems.contains(index) ?
                    Qt::Checked : Qt::Unchecked;

    else if(role == Qt::BackgroundColorRole)
        return checkedItems.contains(index) ?
                    QColor("#ffffb2") : QColor("#ffffff");

    return QSqlQueryModel::data(index, role);
}


///
/// \brief CustomListModel::setData
/// \param index
/// \param value
/// \param role
/// \return
///
bool CheckableListViewModel::setData(const QModelIndex &index,
                                const QVariant &value, int role){

    if(!index.isValid() || role != Qt::CheckStateRole)
        return false;

    if(value == Qt::Checked)
        checkedItems.insert(index);
    else
        checkedItems.remove(index);

    emit dataChanged(index, index);
    return true;
}
