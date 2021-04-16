#ifndef PRELOADVIEWS_H
#define PRELOADVIEWS_H

#include "webservices/dxwengine.h"
#include <QNetworkAccessManager>

LDA_USE_NAMESPACE

/**
 * @brief Unused class
 */
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
