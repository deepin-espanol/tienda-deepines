#include "flattile.h"

#include <QPalette>
#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>

FlatContainer::FlatContainer(QWidget *p) : QWidget(p) {}
FlatTile::FlatTile(QWidget *parent) : QWidget(parent) {}

void FlatContainer::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.fillRect(e->rect(), palette().color(QPalette::ColorGroup::Current, QPalette::ColorRole::Background));
}

void FlatTile::paintEvent(QPaintEvent *e)
{
    QPainter p(this);

    QRect rect = e->rect();
    if ((rect.x() >= 0 && rect.x() <= borderRadius) ||
        (rect.y() >= 0 && rect.y() <= borderRadius) ||
        (rect.bottomRight().x() >= (this->width()-borderRadius) && rect.bottomRight().x() <= this->width()) ||
        (rect.bottomLeft().y() >= (this->height()-borderRadius) && rect.bottomRight().y() <= this->height())) {
        //Means that it could be in a corner area!
        QPainterPath path;
        path.addRoundedRect(this->rect(), borderRadius, borderRadius);
        p.setRenderHint(QPainter::RenderHint::Antialiasing);
        p.fillPath(path, palette().color(QPalette::ColorGroup::Current, QPalette::ColorRole::Base));
    } else {
        p.fillRect(rect, palette().color(QPalette::ColorGroup::Current, QPalette::ColorRole::Base));
    }
}
