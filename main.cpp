#include "commontools/commonstorage.h"
#include "packagewidgets/packagewidget.h"
#include "packagesview.h"
#include "tasksview.h"
#include "filteroptionswidget.h"
#include "mainwindow.h"

#include "ext/libda-release/daddonapplication.h"

#include <QTextStream>
#include <QDebug>
#include <QWidget>
#include <DMainWindow>
#include <QDir>

#include <QApt/Backend>
#include <QApt/Config>

#include <iostream>

DWIDGET_USE_NAMESPACE

const QString icon_path = ":/deepines.svg";

int main(int argc, char *argv[])
{
    //DAddonApplication::loadDXcbPlugin();
    DAddonApplication a(argc, argv);
    a.setWindowIcon(QIcon(icon_path));
    a.setApplicationLicense("GNU GPL v3");
    a.setProductIcon(QIcon(icon_path));
    a.setApplicationVersion("0.0.1");
    a.setApplicationDescription("Tienda Deepines, a community version of the store.");
    a.setApplicationAcknowledgementVisible(false);
    a.setApplicationName("tienda-deepines");
    a.setApplicationDisplayName("Tienda Deepines");

    storage->bkd = new QApt::Backend;
    if (storage->bkd->init()) {
        //We check for DEE repos
        QString URL = "mirror.deepines.com";
        bool found = false;

        int i = 0;
        QFile f("/etc/apt/sources.list");
        if (f.open(QIODevice::OpenModeFlag::ReadOnly)) {
            QStringList list = QString(f.readAll()).split("\n");
            while (i<list.length()) {
                if (list.at(i).startsWith("deb") == true && list.at(i).contains(URL)) {
                    i = list.length();
                    found = true;
                }
                i++;
            }
        }

        (new MainWindow)->show();
    }

    return a.exec();
}
