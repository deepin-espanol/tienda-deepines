#include "commonstorage.h"

#include "commonstorage.h"
#include "filteroptionswidget.h"

#include <iostream>
#include <qapt/backend.h>

PackageModel::PackageModel(QObject *p) : QStandardItemModel(0, 6, p)
{
    setHeaderData(0, Qt::Horizontal, QObject::tr("Name")); //Pkg name
    setHeaderData(1, Qt::Horizontal, QObject::tr("Installed version")); //When you've installed the pkg
    setHeaderData(2, Qt::Horizontal, QObject::tr("Latest version")); //In repos
    setHeaderData(3, Qt::Horizontal, QObject::tr("Architecture")); //Arch that'll be used while installing
    setHeaderData(4, Qt::Horizontal, QObject::tr("Section")); //For its purposes
    setHeaderData(5, Qt::Horizontal, QObject::tr("Status")); //Installed, Update, none
}

QVariant PackageModel::data(const QModelIndex &ind, int role) const
{
    QApt::Package *pkg = CommonStorage::instance()->bkd->package(QStandardItemModel::data(index(ind.row(), 0)).toString());

    if (pkg != nullptr) {
        //std::cout << role << std::endl;
        switch (ind.column()) {
        case 5: return ((pkg->isInUpdatePhase()) ?
                                tr("Updating...") : //If it's not in update, we can retireve the preloaded value
                                 QStandardItemModel::data(ind, role)
                             );
        }
    }
    return QStandardItemModel::data(ind, role);
}

static void addPackage(QApt::Backend *bkd, PackageModel *model, QApt::Package *pk)
{
    QApt::Package *pkg;
    if (bkd != nullptr) {
         pkg = bkd->package(pk->name());
         if (pkg == nullptr) {
             pkg = pk;
         }
    } else {
        pkg = pk;
    }

    model->insertRow(0);
    model->setData(model->index(0, 0), pk->name());
    model->setData(model->index(0, 2), pkg->version());
    model->setData(model->index(0, 3), pkg->architecture());
    model->setData(model->index(0, 4), pkg->section());

    if (pkg->isInstalled() || (QApt::Package::State::Upgradeable & pkg->state())) { // If the installedVersion() is empty but pkg installed, it means that it's the same as the latest version, so use version() then
        if (pkg->installedVersion().isEmpty() != true) {
            model->setData(model->index(0, 1), pkg->installedVersion());
        } else {
            model->setData(model->index(0, 1), pkg->version());
        }
    }
}

PackagesView::PackagesView(QWidget *p) : QTreeView(p)
{
    //Generates models
    m_model = &CommonStorage::instance()->model;
    m_filterWidget = new FilterOptionsWidget;
    m_proxyModel = new SortFilterModel(m_filterWidget);
    m_proxyModel->setSourceModel(m_model);

    //Loads UI
    setRootIsDecorated(false);
    setAlternatingRowColors(true);
    setSortingEnabled(true);
    sortByColumn(0, Qt::AscendingOrder);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    setLineWidth(0);

    QRegExp regExp("", Qt::CaseInsensitive);
    m_proxyModel->setFilterRegExp(regExp);
    setModel(m_proxyModel);

    connect(this, &PackagesView::activated, this, [this](){
        Q_EMIT packageSelected(this->currentIndex().data(0).toString());
    });
    //Update model and all that goes with
    connect(CommonStorage::instance()->bkd, &QApt::Backend::packageChanged, this, [this] () {
        this->setPackages(CommonStorage::instance()->bkd->availablePackages());
    });
}

PackagesView::~PackagesView()
{
    m_filterWidget->~FilterOptionsWidget();
    m_proxyModel->~SortFilterModel();
    this->QTreeView::~QTreeView();
}

void PackagesView::setData(PackageModel *model)
{
    m_model = model;
    m_proxyModel->setSourceModel(model);
}

void PackagesView::setPackages(QApt::PackageList list)
{
    int i = 0;
    while (i < list.length()) {
        if (list.at(i)->isForeignArch() == true && list.at(i)->IsGarbage != true) {
            //We need to pass QApt::Backend. Using the first QApt::Package pointers are wrong. To fix that, we pass the backend, and we'll get a new pointer with correct data by using QApt::Backend::package(QString).
            addPackage(bkd, m_model, list.at(i));
        }
        i++;
    }
}

PackageModel *PackagesView::model() const { return m_model; }
SortFilterModel *PackagesView::proxyModel() const { return m_proxyModel; }
FilterOptionsWidget *PackagesView::filterWidget() const { return m_filterWidget; }
