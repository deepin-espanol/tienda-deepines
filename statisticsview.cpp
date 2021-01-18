#include "statisticsview.h"

#include "Qt/flowlayout.h"
#include "commonstorage.h"

#include <iostream>

StatisticsView::StatisticsView()
{
    contentLayout = new FlowLayout;
    content.setLayout(contentLayout);
    //setViewport(&content);
    content.setContentsMargins(0, 0, 0, 5);
    content.setAutoFillBackground(true);

    this->setWidget(&content);
    this->setWidgetResizable(true);
    this->setAutoFillBackground(true);

    addElement(installedOnes, installedOnes);
    addElement(residualConfOnes, residualConfOnes);
    addElement(orphanedOnes, orphanedOnes);
    addElement(importantOnes, importantOnes);
    addElement(instPolBrokOnes, instPolBrokOnes);
    addElement(nowPolBrokOnes, nowPolBrokOnes);
    addElement(notDownOnes, notDownOnes);
    addElement(nowBrokOnes, nowBrokOnes);
    addElement(updateOnes, updateOnes);
}

void StatisticsView::load(QString)
{
    installedOnes.setTitle(tr("Installed"));
    importantOnes.setTitle(tr("Important packages"));
    nowBrokOnes.setTitle(tr("Broken Packages"));
    updateOnes.setTitle(tr("Updates"));

    installedOnes.setMessage(tr("Installed packages: %1").arg(CommonStorage::instance()->aptData.instPkgs));
    instPolBrokOnes.setMessage(tr("%1 of your APT packages have an Installation Policy broken!.").arg(CommonStorage::instance()->aptData.instPolBrok));
    residualConfOnes.setMessage(tr("You have %1 of your APT packages with residual configurations.").arg(CommonStorage::instance()->aptData.resConf));
    orphanedOnes.setMessage(tr("%1 packages are orphaned in the APT packages.").arg(CommonStorage::instance()->aptData.orphan));
    importantOnes.setMessage(tr("%1 APT packages that are core part of your system.").arg(CommonStorage::instance()->aptData.important));
    notDownOnes.setMessage(tr("We found %1 APT packages that are not downloadable. It might mean you've installed them out of your repos.").arg(CommonStorage::instance()->aptData.notDownl));
    updateOnes.setMessage(tr("Upgradeable APT packages found: %1.").arg(CommonStorage::instance()->aptData.upgradeable));
    nowPolBrokOnes.setMessage(tr("%1 APT packages have their Policy broken now!").arg(CommonStorage::instance()->aptData.nowPolBrok));

    installedOnes.setPercentage(CommonStorage::instance()->aptData.instPkgs*100/CommonStorage::instance()->aptData.total);
    updateOnes.setPercentage(CommonStorage::instance()->aptData.upgradeable*100/CommonStorage::instance()->aptData.instPkgs);
    residualConfOnes.setPercentage(CommonStorage::instance()->aptData.resConf*100/CommonStorage::instance()->aptData.total);
    instPolBrokOnes.setPercentage(CommonStorage::instance()->aptData.instPolBrok*100/CommonStorage::instance()->aptData.instPkgs);
    importantOnes.setPercentage(CommonStorage::instance()->aptData.important*100/CommonStorage::instance()->aptData.instPkgs);
    notDownOnes.setPercentage(CommonStorage::instance()->aptData.notDownl*100/CommonStorage::instance()->aptData.total);
    nowPolBrokOnes.setPercentage(CommonStorage::instance()->aptData.nowPolBrok*100/CommonStorage::instance()->aptData.instPkgs);
}

void StatisticsView::addElement(QWidget *w, AnimatorElement *e)
{
    contentLayout->addWidget(w);
    contentLayout->link(w, e);
}
