#ifndef PROXYDATAMODEL_H
#define PROXYDATAMODEL_H

#include <QSortFilterProxyModel>

class ProxyDataModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit ProxyDataModel(QObject* parent = nullptr);
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

public slots:
    void setSectionFiltered(QString section);

private:
    QString section;
};

#endif // PROXYDATAMODEL_H
