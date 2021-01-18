#include "commonstorage.h"

#include "filteroptionswidget.h"
#include "mainwindow.h"
#include "ext/libda-release/daddonsplittedbar.h"

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
    return QStandardItemModel::data(ind, role);
}

static void addPackage(PackageModel *model, QApt::Package *pk)
{
    QApt::Package *pkg;
    if (CommonStorage::instance()->bkd != nullptr) {
         pkg = CommonStorage::instance()->bkd->package(pk->name());
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
    model->setData(model->index(0, 3), pkg->architecture());
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
        QString pkg = m_proxyModel->data(m_proxyModel->index(currentIndex().row(), 0)).toString();
        if (pkg != "") { //If you click fast enough, the signal is emitted two times before the target loads, so makes a bug.
            Q_EMIT packageSelected(pkg);
        }
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

void PackagesView::load(QString)
{
    //Implement the filtering here

    CommonStorage::instance()->currentWindow->setFillTop(false);
    CommonStorage::instance()->currentWindow->setFillBottom(false);
    CommonStorage::instance()->currentWindow->splitedbar()->setBlurBackground(false);
}

void PackagesView::setData(PackageModel *model)
{
    m_model = model;
    m_proxyModel->setSourceModel(model);
}

using pst = QApt::Package::State;

void PackagesView::setPackages(QApt::PackageList list)
{
    int i = 0;
    CommonStorage::instance()->aptData = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    while (i < list.length()) {
        int state = list.at(i)->state();
        if (state & pst::IsGarbage) {
            CommonStorage::instance()->aptData.garbage++;
        }
        if (state & pst::New) {
            CommonStorage::instance()->aptData.newer++;
        }
        if (state & pst::Orphaned) {
            CommonStorage::instance()->aptData.orphan++;
        }
        if (state & pst::Upgradeable) {
            CommonStorage::instance()->aptData.upgradeable++;
        }
        if (state & pst::NowBroken) {
            CommonStorage::instance()->aptData.nowBrok++;
        }
        if (state & pst::NotDownloadable) {
            CommonStorage::instance()->aptData.notDownl++;
        }
        if (state & pst::NowPolicyBroken) {
            CommonStorage::instance()->aptData.nowPolBrok++;
        }
        if (state & pst::ResidualConfig) {
            CommonStorage::instance()->aptData.resConf++;
        }
        if (state & pst::InstallBroken) {
            CommonStorage::instance()->aptData.instBrok++;
        }
        if (state & pst::InstallPolicyBroken) {
            CommonStorage::instance()->aptData.instPolBrok++;
        }
        if (state & pst::IsImportant) {
            CommonStorage::instance()->aptData.important++;
        }
        if (state & pst::Installed) {
            CommonStorage::instance()->aptData.instPkgs++;
        }

        if (list.at(i)->isForeignArch() == true && list.at(i)->IsGarbage != true) {
            //We need to pass QApt::Backend. Using the first QApt::Package pointers are wrong. To fix that, we pass the backend, and we'll get a new pointer with correct data by using QApt::Backend::package(QString).
            addPackage(m_model, list.at(i));
        }
        i++;
    }
    CommonStorage::instance()->aptData.total = i;
    std::cout << i << " - " << CommonStorage::instance()->aptData.total << std::endl;
}

PackageModel *PackagesView::model() const { return m_model; }
SortFilterModel *PackagesView::proxyModel() const { return m_proxyModel; }
FilterOptionsWidget *PackagesView::filterWidget() const { return m_filterWidget; }
