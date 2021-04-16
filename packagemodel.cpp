#include "packagemodel.h"

PackageModel::PackageModel(QObject *p) : QStandardItemModel(0, 6, p)
{
    setHeaderData(0, Qt::Horizontal, QObject::tr("Name")); //Pkg name
    setHeaderData(1, Qt::Horizontal, QObject::tr("Installed version")); //When you've installed the pkg
    setHeaderData(2, Qt::Horizontal, QObject::tr("Latest version")); //In repos
    setHeaderData(4, Qt::Horizontal, QObject::tr("Section")); //For its purposes
    setHeaderData(5, Qt::Horizontal, QObject::tr("Status")); //Installed, Update, none
}

QVariant PackageModel::data(const QModelIndex &ind, int role) const
{
    return QStandardItemModel::data(ind, role);
}
