#ifndef PACKAGEMODEL_H
#define PACKAGEMODEL_H

#include <QStandardItemModel>

/**
 * @brief UI of the PKGV
 */
class PackageModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit PackageModel(QObject *parent = nullptr);
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};
#endif // PACKAGEMODEL_H
