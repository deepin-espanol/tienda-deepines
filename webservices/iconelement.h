#ifndef ICONELEMENT_H
#define ICONELEMENT_H

#include "webservices/labeladdon.h"

/**
 * @brief Class to display icon from a path, XWE UI Element
 */
class IconElement : public LabelAddon
{
    Q_OBJECT
    Q_PROPERTY(QString src WRITE setSrc READ src NOTIFY srcChanged)
    Q_PROPERTY(QString fromTheme WRITE setFromTheme READ src NOTIFY fromThemeChanged)
public:
    IconElement();

    Q_SIGNAL void srcChanged(QString src);
    Q_SIGNAL void fromThemeChanged(QString src);
    Q_SLOT void setSrc(QString src);
    Q_SLOT void setFromTheme(QString src);
    QString src();

private:
    QString m_src;
    bool isFT = false;
};

#endif // ICONELEMENT_H
