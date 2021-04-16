#include "iconelement.h"

#include <QImage>
#include <QIcon>

IconElement::IconElement() : LabelAddon() {}

QString IconElement::src()
{
    return m_src;
}

void IconElement::setSrc(QString src)
{
    m_src = src;
    QPixmap map;
    map.load(src);
    setPixmap(map);
    isFT = false;
    Q_EMIT srcChanged(src);
}

void IconElement::setFromTheme(QString ft)
{
    m_src = ft;
    setPixmap(QIcon::fromTheme(ft).pixmap(QSize(100, 100)));
    isFT = true;
    Q_EMIT fromThemeChanged(ft);
}
