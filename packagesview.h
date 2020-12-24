#ifndef PACKAGESVIEW_H
#define PACKAGESVIEW_H

#include "sortmodel.h"
#include "abstracthistoryhandler.h"

#include <QStandardItemModel>
#include <QTreeView>
#include <qapt/package.h>

class FilterOptionsWidget;

class PackageModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit PackageModel(QObject *parent = nullptr);
};

class PackagesView : public QTreeView, public AbstractHistoryHandler
{
    Q_OBJECT
public:
    explicit PackagesView(QApt::Backend *bk, QWidget *parent = nullptr);
    ~PackagesView();
    PackageModel *model() const;
    SortFilterModel *proxyModel() const;
    FilterOptionsWidget *filterWidget() const;
    inline virtual QWidget *self() const override {return (QWidget*)(this);}
    inline virtual void load(QString) override {}

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
