#include "packagesview.h"
#include "tasksview.h"
#include "commonstorage.h"
#include "packagewidget.h"
#include "filteroptionswidget.h"
#include "mainwindow.h"

#include "daddonapplication.h"
#include <QTextStream>
#include <iostream>
#include <qapt/backend.h>
#include <qapt/package.h>
#include <qapt/transaction.h>
#include <QDebug>
#include <QWidget>
#include <DMainWindow>

#include <mcheck.h>

DWIDGET_USE_NAMESPACE


void addPackage(PackageModel *model, QApt::Package *pkg)
{
    model->insertRow(0);

    model->setData(model->index(0, 0), (int)(pkg->state()));
    model->setData(model->index(0, 1), pkg->name());
    model->setData(model->index(0, 2), pkg->installedVersion());
    model->setData(model->index(0, 3), pkg->version());
    model->setData(model->index(0, 4), pkg->architecture());
    model->setData(model->index(0, 5), pkg->section());
    model->setData(model->index(0, 6), ((QApt::Package::State::Upgradeable & pkg->state()) ? "Upgradable" : ((QApt::Package::State::Installed & pkg->state()) ? "Installed" : "")));
}

void loadPackages(QApt::PackageList list, PackageModel *model)
{
    int i = 0;
    while (i<list.length()) {
        addPackage(model, list.at(i));
        i++;
    }
}

const QString icon_path = ":/deepines.svg";

int main(int argc, char *argv[])
{
    DAddonApplication::loadDXcbPlugin();
    DAddonApplication a(argc, argv);
    a.setWindowIcon(QIcon(icon_path));
    a.setApplicationLicense("GNU GPL v3");
    a.setProductIcon(QIcon(icon_path));
    a.setApplicationVersion("0.0.1");
    a.setApplicationDescription("Store Deepines, a community version of the store.");
    a.setApplicationAcknowledgementVisible(false);
    a.setApplicationName("store-deepines");
    a.setApplicationDisplayName("Store Deepines");

    QApt::Backend *bkd = &CommonStorage::instance()->bkd;
    if (bkd->init()) {
    /*DMainWindow *win = new DMainWindow;
    TasksManager *mgr = TasksManager::instance();
    PackagesView *pkgs = new PackagesView(bkd, win);
    PackageWidget *wi = new PackageWidget;
    win->setCentralWidget(pkgs);

    QApt::PackageList availablePackages;
    QApt::PackageList pkgList = bkd->availablePackages();

    int i = 0;
    while (i < pkgList.length()) {
        if (pkgList.at(i)->isForeignArch() == true && pkgList.at(i)->IsGarbage != true) {
            availablePackages << bkd->availablePackages().at(i);
        }
        i++;
    }

    //pkgList.~QList();
    pkgs->setPackages(availablePackages);
    //availablePackages.~QList();

    QObject::connect(pkgs, &PackagesView::packageSelected, bkd, [bkd, wi](QString pkg) {
        wi->setPackage(bkd->package(pkg));
    });
    QObject::connect(wi, &PackageWidget::reopen, bkd, [bkd, wi](QString pkg) {
        wi->setPackage(bkd->package(pkg));
    });

    pkgs->filterWidget()->show();
    wi->show();
    mgr->view()->show();
    win->show();*/

    mtrace();

    (new MainWindow)->show();

    }

    return a.exec();
}
