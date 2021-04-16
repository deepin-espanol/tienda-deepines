#ifndef BANNERELEMENT_H
#define BANNERELEMENT_H

#include "ext/libda-release/basicelements.h"

#include <QWidget>

LDA_USE_NAMESPACE

class QNetworkReply;

/**
 * @brief Section banner XWE UI Element
 */
class BannerElement : public Widget
{
    Q_OBJECT
    Q_PROPERTY(QString url WRITE setUrl NOTIFY urlChanged)
public:
    explicit BannerElement();
    inline virtual QObject *self() override {return this;}
    void setUrl(QString url);

Q_SIGNALS:
    void urlChanged(QString url);

protected Q_SLOTS:
    void handleResponse();

protected:
    void paintEvent(QPaintEvent *e) override;

private:
    QPixmap img;
    bool hasLoaded = false;
    QNetworkReply *ans;
};

#endif // BANNERELEMENT_H
