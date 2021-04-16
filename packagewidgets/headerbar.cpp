#include "headerbar.h"

#include "ext/libda-release/sharednam.h"

#include <QPaintEvent>
#include <QPainter>
#include <QImage>
#include <QImageReader>
#include <QNetworkReply>
#include <QPalette>
#include <QIcon>

HeaderBar::HeaderBar(QWidget *parent) : QWidget(parent)
{
    img.load(":/images/default-banner.jpg");
}

void HeaderBar::load(QUrl url)
{
    QNetworkReply *rep = Dtk::Addons::SharedNAM::instance()->pendingGet(QNetworkRequest(url));
    if (rep->error() != QNetworkReply::NetworkError::NoError) {
        img.load(":/images/default-banner.jpg");
    } else {
        img = QPixmap::fromImage(QImageReader(rep).read());
    }
}

void HeaderBar::setName(QString name)
{
    m_name = name;
    update();
}

void HeaderBar::setWidget(QWidget *w)
{
    m = w;
    m->setParent(this);
}

void HeaderBar::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
    checkSizes();
}

void HeaderBar::checkSizes()
{
    if (m != nullptr) {
        //10 cause there's the scrollbar
        m->move(width()
                - 10
                - m->width(),
                height()
                - 5
                - m->height()
               );
    }
}

void HeaderBar::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    paint.drawPixmap(0, 0, img.scaled(width(), height(), Qt::KeepAspectRatioByExpanding));

    QLinearGradient m_gradient(rect().topLeft(), rect().bottomLeft());
    m_gradient.setColorAt(0.2, Qt::transparent);
    m_gradient.setColorAt(0.95, QPalette().color(QPalette::ColorGroup::Current, QPalette::ColorRole::Window));

    paint.fillRect(QRect(0, 0, width(), height()), m_gradient);

    //Put the image
    paint.drawPixmap(QRect(5, this->height() - 65, 60, 60), QIcon::fromTheme(m_name).pixmap(QSize(60, 60)), QRect(0, 0, 60, 60));

    //Put the text
    QFont f = this->font();
    f.setBold(true);
    f.setWeight(20);
    f.setPixelSize(23);

    QPointF targ(70, this->height() - 5 - QFontMetrics(f).height());
    paint.setPen(QPalette().color(QPalette::ColorGroup::Current, QPalette::ColorRole::Text));
    paint.setFont(f);
    paint.drawText(targ, m_name);
}
