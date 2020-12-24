#include "preloadviews.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include "sharednam.h"
#include <QWidget>
#include <QMetaObject>
#include <iostream>

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

    if (got->error() != QNetworkReply::NetworkError::NoError) {
        //[TODO] generate a widget that shows that there's a web error
        std::cout << got->errorString().toLocal8Bit().data() << std::endl;
    } else {
        if (engine == nullptr) {
            engine = new DXWEngine;
        }
        //Engine loads will return boolean in the future to know if the parsing fails or not.
        //[TODO] generate a widget that says there's an error in the parsing
        engine->loadXML(got->readAll());
        if (QString(engine->rootElement()->self()->metaObject()->className()) == "PageWidget") {
            return dynamic_cast<AbstractHistoryHandler *>(dynamic_cast<PageWidget *>(engine->rootElement()->self()));
        }
    }
    //[TODO] generate a widget that there's an error in the file content (root element not good, not PageViews (alias Page)).
    return new AbstractHistoryHandler;
}
