#include "packagesview.h"
#include "tasksview.h"
#include "commonstorage.h"
#include "packagewidget.h"
#include "filteroptionswidget.h"
#include "mainwindow.h"
#include "nodeepineswarn.h"

#include "ext/libda-release/daddonapplication.h"

#include <QTextStream>
#include <iostream>
#include <qapt/backend.h>
#include <qapt/config.h>
#include <QDebug>
#include <QWidget>
#include <DMainWindow>
#include <QDir>

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

    storage->bkd = new QApt::Backend;
    if (storage->bkd->init()) {
        mtrace();

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

        if (!found) {
            QDir dir("/etc/apt/sources.list.d");
            if (dir.exists()) {
                QStringList list = dir.entryList(QDir::Filter::Files);
                int j = 0;
                while (j<list.length()) {
                    QFile f(list.at(j));
                    if (f.open(QIODevice::OpenModeFlag::ReadOnly)) {
                        QStringList strings = QString(f.readAll()).split("\n");
                        i = 0;
                        while (i<strings.length()) {
                            if (strings.at(i).startsWith("deb") && strings.at(i).contains(URL)) {
                                i = strings.length();
                                j = list.length();
                                found = true;
                            }
                            i++;
                        }
                    }

                    j++;
                }
            }
        }

        if (!found) {
            (new NoDeepinesWarn)->generatePopup();
        }

        (new MainWindow)->show();

        /*
        QApt::Transaction *trans = storage->bkd->commitChanges();
        trans->run();
        trans->connect(trans, &QApt::Transaction::finished, trans, [](QApt::ExitStatus st) {(new MainWindow)->show();});*/


        /*storage->bkd->markPackageForRemoval("2048-qt");
        QApt::Transaction *trans = storage->bkd->commitChanges();
        trans->run();
        trans->connect(trans, &QApt::Transaction::finished, trans, [](QApt::ExitStatus st) {std::cout << st << std::endl;});*/
    }

    return a.exec();
}
