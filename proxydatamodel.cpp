#include "proxydatamodel.h"

ProxyDataModel::ProxyDataModel(QObject *parent): QSortFilterProxyModel(parent) {}

void ProxyDataModel::setSectionFiltered(QString sect)
{
    if(sect != section)
        section = sect;
    invalidateFilter();
}

bool ProxyDataModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if (section != "") {
        if (sourceModel()->data(sourceModel()->index(source_row, 5, source_parent)).toString() == section) {
             return false;
        }
    }
    return true;
}

QVariant ProxyDataModel::headerData(int section, Qt::Orientation orientation,
                                int role) const {
    return sourceModel()->headerData(section, orientation,
                                     role);
}
