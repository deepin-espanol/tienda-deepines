#include "preloadviews.h"

#include <iostream>

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QWidget>
#include <QMetaObject>
#include <QFile>
#include <QTimer>
#include <QRegExp>

#include "ext/libda-release/sharednam.h"

PreloadViews::PreloadViews(QObject *parent) : QObject(parent) {}

PreloadViews::~PreloadViews()
{
    engine->destroyAllElements();
    engine->~DXWEngine();
}

LDA_USE_NAMESPACE

AbstractHistoryHandler *PreloadViews::load(QString p)
{
    QNetworkReply *got = nullptr;
    if ((p.startsWith("qrc:") || p.startsWith("file:")) == false) {
        got = SharedNAM::instance()->pendingGet(QNetworkRequest(p));
    }

    if (engine == nullptr) {
        engine = new DXWEngine;
    }

    if ((got != nullptr && got->error() != QNetworkReply::NoError) ||
        //Github raw just retrieve a string with XXX: Error description
        (got && (QString(got->readAll())).contains(QRegExp("([0-9]+): ([a-zA-Z0-9 ]+)"))) ||
        ((p.startsWith("qrc:") || p.startsWith("file:")) == false)) {

        //Show error
        QFile f(":/XWE/fallback.xwe");
        f.open(QIODevice::OpenModeFlag::ReadOnly);
        if (engine->loadXML(f.readAll()) == false) {
            //std::cout << "Failed to load file!" << std::endl;
        }
        f.close();
        if (PageWidget *w = dynamic_cast<PageWidget *>(engine->rootElement()->self())) {
            return w;
        }
    } else {
        if ((p.startsWith("qrc:") || p.startsWith("file:")) == false) {
            if (engine->loadXML(got->readAll()) == false) {
                //std::cout << "Failed to parse XML data!" << std::endl;
            }
        } else {
            QFile f(p.replace("qrc:/", ":/").replace("file://", "/"));
            f.open(QIODevice::OpenModeFlag::ReadOnly);
            if (engine->loadXML(f.readAll()) == false) {
                //std::cout << "Failed to load file!" << std::endl;
            }
            f.close();
        }
        if (PageWidget *target = dynamic_cast<PageWidget *>(engine->rootElement())) {
            return target;
        } else {
            engine->destroyAllElements();
            QFile f(":/XWE/error.xwe");
            f.open(QIODevice::OpenModeFlag::ReadOnly);
            engine->loadXML(f.readAll());
            f.close();
            if (PageWidget *w = dynamic_cast<PageWidget *>(engine->rootElement())) {
                return w;
            }
        }
    }
    return new PageWidget;
}
