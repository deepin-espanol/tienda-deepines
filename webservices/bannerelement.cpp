#include "bannerelement.h"

#include <QPainter>
#include <QImageReader>
#include <QNetworkReply>
#include "ext/libda-release/sharednam.h"

BannerElement::BannerElement() : Widget()
{
    setFixedHeight(150);
}

void BannerElement::handleResponse()
{
    if (ans->error() != QNetworkReply::NetworkError::NoError) {
        img.load(":/images/default-banner.jpg");
    } else {
        img = QPixmap::fromImage(QImageReader(ans).read());
    }
}

void BannerElement::setUrl(QString url)
{
    ans = Dtk::Addons::SharedNAM::instance()->get(QNetworkRequest(url));
    connect(ans, &QNetworkReply::finished, this, &BannerElement::handleResponse);
    hasLoaded = true;
}

void BannerElement::paintEvent(QPaintEvent *)
{
    QPainter paint(this);

    if (hasLoaded) {
        paint.drawPixmap(0, 0, img.scaled(width(), height(), Qt::KeepAspectRatioByExpanding));

        QLinearGradient m_gradient(rect().topLeft(), rect().bottomLeft());
        m_gradient.setColorAt(0.2, Qt::transparent);
        m_gradient.setColorAt(0.95, QPalette().color(QPalette::ColorGroup::Current, QPalette::ColorRole::Window));

        paint.fillRect(QRect(0, 0, width(), height()), m_gradient);
    }

    QString m_name = property("text").toString();

    //Put the text
    QFont f = this->font();
    f.setBold(true);
    f.setWeight(80);
    f.setPixelSize(73);

    QPointF targ(70, this->height() - 5 - QFontMetrics(f).height()/2);
    paint.setPen(QPalette().color(QPalette::ColorGroup::Current, QPalette::ColorRole::Text));
    paint.setFont(f);
    paint.drawText(targ, m_name);
}
