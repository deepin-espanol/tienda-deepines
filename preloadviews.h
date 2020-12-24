#ifndef PRELOADVIEWS_H
#define PRELOADVIEWS_H

#include "dxwengine.h"
#include <QNetworkAccessManager>

LDA_USE_NAMESPACE

class PreloadViews : public QObject
{
    Q_OBJECT
public:
    explicit PreloadViews(QObject *parent = nullptr);
    ~PreloadViews();

    AbstractHistoryHandler *load(QString path);

private:
    DXWEngine *engine = nullptr;
};

#endif // PRELOADVIEWS_H
