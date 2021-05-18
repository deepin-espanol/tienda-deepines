#include "packagesview.h"

#include <iostream>

#include <qapt/backend.h>

#include "ext/libda-release/daddonsplittedbar.h"

#include "commontools/commonstorage.h"
#include "packagemodel.h"
#include "filteroptionswidget.h"
#include "mainwindow.h"


static void addPackage(PackageModel *model, QApt::Package *pk)
{
    QApt::Package *pkg;
    if (storage->bkd != nullptr) {
         pkg = storage->bkd->package(pk->name());
         if (pkg == nullptr) {
             pkg = pk;
         }
    } else {
        std::cout << "Failed to get the package from the BKD." << std::endl;
        pkg = pk;
    }

    model->insertRow(0);
    model->setData(model->index(0, 0), pk->name());
    model->setData(model->index(0, 2), pkg->version());
    model->setData(model->index(0, 4), pkg->section());

    if (pkg->isInstalled() || (QApt::Package::State::Upgradeable & pkg->state())) { // If the installedVersion() is empty but pkg installed, it means that it's the same as the latest version, so use version() then
        if (pkg->installedVersion().isEmpty() != true) {
            model->setData(model->index(0, 1), pkg->installedVersion());
        } else {
            model->setData(model->index(0, 1), pkg->version());
        }
    }

    QString val = "";

    if (QApt::Package::State::Upgradeable & pkg->state()) {
        val += QObject::tr("Upgradeable");
    } else if (pkg->isInstalled()) {
        val += QObject::tr("Installed");
    }

    if (pkg->isInUpdatePhase()) { //Means that the PKG have been said as being updated (devs)
        val += QObject::tr(", a new version is coming");
    }

    model->setData(model->index(0, 5), val);
}

PackagesView::PackagesView(QWidget *p) : QTreeView(p)
{
    //Generates models
    m_model = &storage->model;
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
        QString pkg = m_proxyModel->data(m_proxyModel->index(currentIndex().row(), 0)).toString();
        if (pkg != "") { //If you click fast enough, the signal is emitted two times before the target loads, so makes a bug.
            Q_EMIT packageSelected(pkg);
        }
    });
    //Update model and all that goes with
    connect(storage->bkd, &QApt::Backend::packageChanged, this, [this] () {
        this->setPackages(storage->bkd->availablePackages());
    });
}

PackagesView::~PackagesView()
{
    m_filterWidget->~FilterOptionsWidget();
    m_proxyModel->~SortFilterModel();
    this->QTreeView::~QTreeView();
}

void PackagesView::load(QString)
{
    //Implement the filtering here

    wmgr->fillTop(false);
    wmgr->fillBottom(true);
    wmgr->blurTop(false);
}

void PackagesView::setData(PackageModel *model)
{
    m_model = model;
    m_proxyModel->setSourceModel(model);
}

#include <QDebug>

void PackagesView::setPackages(QApt::PackageList list)
{
    qInfo() << storage->bkd->origins();
    int i = 0;
    while (i < list.length()) {
        if (list[i]->site() == "repositorio.deepines.com") {
            addPackage(m_model, list.at(i));
        }
        i++;
    }
}

PackageModel *PackagesView::model() const { return m_model; }
SortFilterModel *PackagesView::proxyModel() const { return m_proxyModel; }
FilterOptionsWidget *PackagesView::filterWidget() const { return m_filterWidget; }
