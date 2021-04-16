#ifndef PACKAGESVIEW_H
#define PACKAGESVIEW_H

#include "sortmodel.h"
#include "packagemodel.h"
#include "commontools/historymanager.h"

#include <QStandardItemModel>
#include <QTreeView>

class FilterOptionsWidget;
class PackagesView;

namespace QApt {
    class Backend;
    class Package;
}

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
    void setPackages(QList<QApt::Package*> list);

private:
    PackageModel *m_model = nullptr;
    SortFilterModel *m_proxyModel = nullptr;
    FilterOptionsWidget *m_filterWidget = nullptr;
    QApt::Backend *bkd = nullptr;
};

#endif // PACKAGESVIEW_H
