#ifndef EFFECTWIDGET_H
#define EFFECTWIDGET_H

#include "libda_global.h"

#include <dtkwidget_global.h>
#include <DObject>

#include <QWidget>

class VisualEffect;

LDA_BEGIN_NAMESPACE

class EffectWidgetPrivate;

/**
 * @brief EffectWidget class is used for graphical effects rendered with what's behind it
 */

class LIBDA_SHARED_EXPORT EffectWidget : public QWidget, public DTK_CORE_NAMESPACE::DObject
{
    Q_OBJECT

    Q_PROPERTY(int radius READ radius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(QColor maskColor READ maskColor WRITE setMaskColor NOTIFY maskColorChanged)
    Q_PROPERTY(bool full READ isFull WRITE setFull NOTIFY fullChanged)
    Q_PROPERTY(bool blurEnabled READ blurEnabled WRITE setBlurEnabled NOTIFY blurEnabledChanged)

public:
    enum BlurMode {
        GaussianBlur
    };

    Q_ENUMS(BlurMode)

    enum BlurEffectType {
        Masked,
        Full
    };

    Q_ENUMS(BlendMode)

    enum MaskColorType {
        DarkColor,
        LightColor,
        AutoColor,
        CustomColor
    };

    Q_ENUMS(MaskColorType)

    explicit EffectWidget(QWidget *parent = nullptr);
    ~EffectWidget() override;

    int radius() const;

    bool isFull() const;
    bool blurEnabled() const;
    QColor maskColor() const;

    /**
     * @brief Use custom source image
     * @param image
     * @param autoScale
     */
    void setSourceImage(const QImage &image, bool autoScale = true);

    VisualEffect *effect;

public Q_SLOTS:
    /**
     * @brief Set blur radius
     * @param radius
     */
    void setRadius(int radius);

    void setMaskColor(QColor maskColor);
    void setMaskColor(MaskColorType type);
    void setFull(bool full);
    /**
     * @brief Set if blur [or any effects] have to be enabled
     * @param blurEnabled
     */
    void setBlurEnabled(bool blurEnabled);
    /**
     * @brief Masked Bend mode direction
     * @param e
     */
    void setDirection(Qt::Edge e);

    /**
     * @brief Update region used to get image on which we perform visual effects
     * @param ren
     */
    void updateBlurSourceImage(const QRegion &ren);

Q_SIGNALS:
    void radiusChanged(int radius);
    void modeChanged(BlurMode mode);

    void effectTypeChanged(BlurEffectType blendMode);
    void blurRectXRadiusChanged(int blurRectXRadius);
    void blurRectYRadiusChanged(int blurRectYRadius);
    void maskAlphaChanged(quint8 alpha);
    void maskColorChanged(QColor maskColor);
    void fullChanged(bool full);
    void blurEnabledChanged(bool blurEnabled);

    void blurSourceImageDirtied();

protected:
    EffectWidget(EffectWidgetPrivate &dd, QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void moveEvent(QMoveEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void showEvent(QShowEvent *event) Q_DECL_OVERRIDE;
    void hideEvent(QHideEvent *event) Q_DECL_OVERRIDE;
    void changeEvent(QEvent *event) Q_DECL_OVERRIDE;
    bool eventFilter(QObject *watched, QEvent *event) override;

    //Some optimizations canbe done for some of these mods, the ones which needn't a COMPLETE calculation.
    void paintMaskedBlurEffect(QPainter &painter);  //Instead of full, get hor or vert to then calculate with the selected direction.
    void paintBlurEffect(QPainter &painter); //Just the rect
    void paintBlurChannel(QPainter &painter); //Just the rect
    void paintSplittedChannels(QPainter &painter); //Just the rect
    void paintGrayScale(QPainter &painter); //Just the rect

private:
    D_DECLARE_PRIVATE(EffectWidget)
    Qt::Edge direction = Qt::Edge::BottomEdge;
    int internal_blur_radius = 5;
};

LDA_END_NAMESPACE

#endif // EFFECTWIDGET_H
