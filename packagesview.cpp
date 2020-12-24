#include "commonstorage.h"

#include "filteroptionswidget.h"
#include <iostream>
#include <qapt/backend.h>

PackageModel::PackageModel(QObject *p) : QStandardItemModel(0, 7, p)
{
    setHeaderData(0, Qt::Horizontal, QObject::tr("Name")); //Pkg name
    setHeaderData(1, Qt::Horizontal, QObject::tr("Installed version")); //When you've installed the pkg
    setHeaderData(2, Qt::Horizontal, QObject::tr("Latest version")); //In repos
    setHeaderData(3, Qt::Horizontal, QObject::tr("Architecture")); //Arch that'll be used while installing
    setHeaderData(4, Qt::Horizontal, QObject::tr("Section")); //For its purposes
    setHeaderData(5, Qt::Horizontal, QObject::tr("Status")); //Installed, Update, none
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

    QString val = "";
    if (pkg->isInstalled() || (QApt::Package::State::Upgradeable & pkg->state()) != 0) {
        if ((QApt::Package::State::Upgradeable & pkg->state()) != 0) {
            val = "Upgradeable";
        } else {
            val = "Installed";
        }
    }

    if (pkg->name() == "libfreetype6" || pkg->name() == "2048-qt") {
        std::cout << "value: " << val.toLocal8Bit().data()
                  << ", real: " << pkg->isInstalled()
                  << ", needs: " << ((QApt::Package::State::Installed & pkg->state()) != 0)
                  << ", or: "<< ((QApt::Package::State::Upgradeable & pkg->state()) != 0) << std::endl;
    }

    model->setData(model->index(0, 5), val);

    if (pkg->isInstalled() || (QApt::Package::State::Upgradeable & pkg->state())) { // If the installedVersion() is empty but pkg installed, it means that it's the same as the latest version, so use version() then
        if (pkg->installedVersion().isEmpty() != true) {
            model->setData(model->index(0, 1), pkg->installedVersion());
        } else {
            model->setData(model->index(0, 1), pkg->version());
        }
    }
}

PackagesView::PackagesView(QApt::Backend *kd, QWidget *p) : QTreeView(p)
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
    sortByColumn(1, Qt::AscendingOrder);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);

    QRegExp regExp("", Qt::CaseInsensitive);
    m_proxyModel->setFilterRegExp(regExp);
    setModel(m_proxyModel);

    connect(this, &PackagesView::activated, this, [this](){
        Q_EMIT packageSelected(this->currentIndex().data(2).toString());
    });

    bkd = kd;
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
    while (i<list.length()) {
        //We need to pass QApt::Backend. Using the first QApt::Package pointers are wrong. To fix that, we pass the backend, and we'll get a new pointer with correct data by using QApt::Backend::package(QString).
        addPackage(bkd, m_model, list.at(i));
        i++;
    }
}

PackageModel *PackagesView::model() const { return m_model; }
SortFilterModel *PackagesView::proxyModel() const { return m_proxyModel; }
FilterOptionsWidget *PackagesView::filterWidget() const { return m_filterWidget; }
