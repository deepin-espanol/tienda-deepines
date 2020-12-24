#ifndef DYNAMICSVGPARSER_H
#define DYNAMICSVGPARSER_H

#include "class_decl.h"
#include "libda_global.h"

#include <QPalette>

LDA_BEGIN_NAMESPACE

/**
 * @brief DynamicSvgParser provides good interface and features for "dynamic" SVGs: some colors can be the ones of the cureent palette!
 * @brief While using fill prop., use: ${value} or ${value1|value2}, if one is provided, the same will be used in every states.
 * @brief To use a QPalette property, use $<QPalette::ColorRole> and as text. Otherwise, you can use a custom value too.
 */
class LIBDA_SHARED_EXPORT DynamicSvgParser : public QObject
{
    Q_OBJECT
public:
    explicit DynamicSvgParser(QByteArray arr, QPalette source, QObject *parent = nullptr);
    /**
     * @brief Pixmap result. Should always be called to get the pixmap as data can change at any time
     * @return
     */
    QPixmap *result();
    /**
     * @brief Tells you if we're using the default value or the second one
     * @return
     */
    bool isToggled();
    /**
     * @brief Is caching feature enabled
     * @return
     */
    bool isCaching();
    /**
     * @brief Size of the pixmap and the size by which it is binded to get the pixmap
     * @return
     */
    QSize renderedSize();

public Q_SLOTS:
    /**
     * @brief Change Palette source
     */
    void setSource(QPalette);
    /**
     * @brief Change input svg image
     * @param arr
     */
    void setInput(QByteArray arr);
    /**
     * @brief Toggle between the two states handled by the svg
     */
    void toggle();
    /**
     * @brief Use toggled or non toggled version
     */
    void setToggled(bool = true);
    /**
     * @brief Keeps in memory the two versions (toggled and non one) in memory
     * @param enable
     */
    void setCaching(bool enable = true);
    /**
     * @brief If you want to render on a huge area, change the value to get not pixelized image
     * @param size
     */
    void setRenderedSize(QSize size);
    /**
     * @brief If you want to reload, internals handles it well, but in the case
     */
    void clearCache();

private:
    QSize rendered = QSize(25, 25);
    bool caching = false;
    bool toggled = false;
    bool mustReload = false;
    QPalette src;
    QByteArray data;
    QPixmap *firstVersion = nullptr;
    QPixmap *secondVersion = nullptr;
};

LDA_END_NAMESPACE

#endif // DYNAMICSVGPARSER_H
