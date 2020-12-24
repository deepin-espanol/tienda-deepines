#ifndef EFFECTWIDGET_P_H
#define EFFECTWIDGET_P_H

#include <QPainterPath>
#include <DObjectPrivate>
#include "effectwidget.h"

LDA_BEGIN_NAMESPACE

class EffectWidgetPrivate : public DTK_CORE_NAMESPACE::DObjectPrivate
{
public:
    EffectWidgetPrivate(EffectWidget *qq);

    EffectWidget::BlurMode mode = EffectWidget::GaussianBlur;
    QImage sourceImage;
    bool customSourceImage = false;
    bool autoScaleSourceImage = false;

    int radius = 35;
    qint16 maskAlpha = -1;

    bool full = false;
    bool blurEnabled = true;

    QColor maskColor = Qt::transparent;
    EffectWidget::MaskColorType maskColorType = EffectWidget::AutoColor;
    QPainterPath maskPath;

    bool isFull() const;

    void setMaskColor(const QColor &color);
    void setMaskAlpha(const quint8 alpha);
    quint8 getMaskColorAlpha() const;
    QColor getMaskColor(const QColor &baseColor) const;

    void resetSourceImage();

private:
    D_DECLARE_PUBLIC(EffectWidget)
};

LDA_END_NAMESPACE

#endif // EFFECTWIDGET_P_H
