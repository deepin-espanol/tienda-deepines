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


const QString icon_path = ":/deepines.svg";

int main(int argc, char *argv[])
{
    DAddonApplication::loadDXcbPlugin();
    DAddonApplication a(argc, argv);
    a.setWindowIcon(QIcon(icon_path));
    a.setApplicationLicense("GNU GPL v3");
    a.setProductIcon(QIcon(icon_path));
    a.setApplicationVersion("0.0.1");
    a.setApplicationDescription("Tienda Deepines, a community version of the store.");
    a.setApplicationAcknowledgementVisible(false);
    a.setApplicationName("tienda-deepines");
    a.setApplicationDisplayName("Tienda Deepines");

    CommonStorage::instance()->bkd = new QApt::Backend;
    QApt::Backend *bkd = CommonStorage::instance()->bkd;
    if (bkd->init()) {
        mtrace();
        (new MainWindow(bkd))->show();
    }

    return a.exec();
}
