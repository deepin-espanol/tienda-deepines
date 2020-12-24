#include "preloadviews.h"

#include <QNetworkRequest>
#include <QNetworkReply>
#include "sharednam.h"
#include <QWidget>
#include <QMetaObject>
#include <QEventLoop>
#include <iostream>

PreloadViews::PreloadViews(QObject *parent) : QObject(parent) {}

PreloadViews::~PreloadViews()
{
    engine->~DXWEngine();
}

LDA_USE_NAMESPACE

QWidget *PreloadViews::load(QString p)
{
    if (nam == nullptr) {
        nam = new QNetworkAccessManager(this);
    }
    QNetworkRequest req(p);
    QNetworkReply *got = nam->get(req);

    QEventLoop loop;
    connect(got, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    //req.~QNetworkRequest();

    if (got->error() != QNetworkReply::NetworkError::NoError) {
        std::cout << got->errorString().toLocal8Bit().data() << std::endl;
    } else {
        if (engine == nullptr) {
            engine = new DXWEngine;
        }
        QString d = got->readAll();
        engine->loadXML(d);
        std::cout << engine->rootElement()->self()->metaObject()->className() << std::endl;
        if (QWidget *w = qobject_cast<QWidget *>(engine->rootElement()->self())) {
            return w;
        } else {
            std::cout << "Unable to slice to QWidget :(" << std::endl;
        }
    }
    return new QWidget;
}
