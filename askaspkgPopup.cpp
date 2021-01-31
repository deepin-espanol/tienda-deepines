#include "askaspkgPopup.h"

#include <DDialog>
#include <iostream>

DWIDGET_USE_NAMESPACE

bool Popups::askAsPackage(QString pkgName)
{
    DDialog *dial = new DDialog;
    dial->setIcon(QIcon::fromTheme("warning"));
    dial->setTitle(QObject::tr("Choose an option"));
    dial->setMessage(QObject::tr("You've selected %1 that is available over APT repositories.\nPlease choose one of the following options for the package.").arg(pkgName));

    dial->clearButtons();
    int pkg = dial->addButton(QObject::tr("Package file"), true, DDialog::ButtonType::ButtonRecommend);
    dial->addButton(QObject::tr("Repo package"), false, DDialog::ButtonType::ButtonNormal);

    bool good = false;
    QObject::connect(dial, &DDialog::buttonClicked, dial, [pkg, &good] (int btn) {good = (btn == pkg);});

    dial->setWindowModality(Qt::WindowModality::ApplicationModal);
    std::cout << "Running dialog" << std::endl;
    dial->exec();

    return good;
}
