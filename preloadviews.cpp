#include "preloadviews.h"

#include <iostream>

#include <QNetworkRequest>
#include <QNetworkReply>
#include <QWidget>
#include <QMetaObject>

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
    QNetworkReply *got = SharedNAM::instance()->pendingGet(QNetworkRequest(p));

    if (engine == nullptr) {
        engine = new DXWEngine;
    }
    if (got->error() != QNetworkReply::NetworkError::NoError) {
        //Show error
        QFile f(":/XWE/fallback.xwe");
        f.open(QIODevice::OpenModeFlag::ReadOnly);
        engine->loadXML(f.readAll());
        f.close();
        return dynamic_cast<PageWidget *>(engine->rootElement()->self());
    } else {
        //Engine loads will return boolean in the future to know if the parsing fails or not.
        //[TODO] generate a widget that says there's an error in the parsing
        engine->loadXML(got->readAll());
        if (QString(engine->rootElement()->self()->metaObject()->className()) == "PageWidget") {
            return dynamic_cast<PageWidget *>(engine->rootElement()->self());
        } else {
            engine->destroyAllElements();
            QFile f(":/XWE/error.xwe");
            f.open(QIODevice::OpenModeFlag::ReadOnly);
            engine->loadXML(f.readAll());
            f.close();
            return dynamic_cast<PageWidget *>(engine->rootElement()->self());
        }
    }
    //[TODO] generate a widget that there's an error in the file content (root element not good, not PageViews (alias Page)).
    return new AbstractHistoryHandler;
}
