#ifndef IMAGERY_H
#define IMAGERY_H

#include <QPixmap>

QPixmap blur(const QPixmap& image, const QRect& rect, int radius, bool alphaOnly = false);

#endif // IMAGERY_H
