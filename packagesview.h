#ifndef PACKAGESVIEW_H
#define PACKAGESVIEW_H

#include "sortmodel.h"
#include "historymanager.h"

#include <QStandardItemModel>
#include <QTreeView>
#include <QApt/Package>

class FilterOptionsWidget;

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

/**
 * @brief PKGV class, shows all provided PKGS
 */
class PackagesView : public QTreeView, public AbstractHistoryHandler
{
    Q_OBJECT
public:
    explicit PackagesView(QWidget *parent = nullptr);
    ~PackagesView() override;
    PackageModel *model() const;
    SortFilterModel *proxyModel() const;
    FilterOptionsWidget *filterWidget() const;
    inline virtual QWidget *widget() const override {return (QWidget*)(this);}
    virtual void load(QString) override;

Q_SIGNALS:
    void packageSelected(QString pkgName);

public Q_SLOTS:
    void setData(PackageModel *model);
    void setPackages(QApt::PackageList list);

private:
    PackageModel *m_model = nullptr;
    SortFilterModel *m_proxyModel = nullptr;
    FilterOptionsWidget *m_filterWidget = nullptr;
    QApt::Backend *bkd = nullptr;
};

#endif // PACKAGESVIEW_H
