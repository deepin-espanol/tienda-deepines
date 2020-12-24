#ifndef MULTICOLORS_H
#define MULTICOLORS_H

#include "libda_global.h"
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>

LDA_BEGIN_NAMESPACE

/**
 * @brief Class used for Ui tests, generates multicolor squares
 */
class LIBDA_SHARED_EXPORT MultiColors : public QWidget
{
    Q_OBJECT
public:
    explicit MultiColors(QWidget *parent = nullptr);

    /**
     * @brief rectangleSize, the size of the squares rendered
     */
    int rectangleSize = 80;

protected:
    void paintEvent(QPaintEvent *e) override;
    inline void resizeEvent(QResizeEvent *e) override {qDebug() << this->size(); QWidget::resizeEvent(e); update(); }
};

LDA_END_NAMESPACE

#endif // MULTICOLORS_H
