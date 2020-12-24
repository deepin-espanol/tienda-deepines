#ifndef GRAPHICTOOLS_H
#define GRAPHICTOOLS_H

#include "libda_global.h"
#include <QGraphicsBlurEffect>
#include <QGraphicsEffect>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPainter>

LDA_BEGIN_NAMESPACE

/**
 * @brief VisualEffect class is used to perform effects on images, like blur or filters
 */
class  LIBDA_SHARED_EXPORT VisualEffect {
public:
    enum ColorChannel {
        Red =   8,
        Green = 2,
        Blue =  4,
        Alpha = 1
    };
    enum EffectType {
        Blur             = 1,
        Masked           = 2,
        ChannelBlur      = 4,
        SplittedChannels = 8,
        GrayScale        = 16
    };
    enum ChannelSplitDirection {
        Right   = 1,
        Left    = 2,
        Bottom  = 4,
        Top     = 8
    };
    enum ChannelSplitMode {
        Exclude = 1,
        Include = 2
    };

    int splitPadding = 5;
    EffectType type = EffectType::Blur;
    int channel = ColorChannel::Green;
    ChannelSplitMode splitMode = ChannelSplitMode::Exclude;
    ChannelSplitDirection direction = ChannelSplitDirection::Top;
};

LDA_END_NAMESPACE

/**
 * @brief Image alpha gradient on the image
 * @param input
 * @param edge
 * @return As a magic transformed image
 */
QImage transformAlpha(QImage input, Qt::Edge edge);

/**
 * @brief Split channels with the settings choosen.
 * @param src
 * @param channel
 * @param mode
 * @param direction
 * @param padding
 * @return Image with applyed settings
 */
QImage splitChannel(QImage src, int channel = Dtk::Addons::VisualEffect::ColorChannel::Red, Dtk::Addons::VisualEffect::ChannelSplitMode mode = Dtk::Addons::VisualEffect::ChannelSplitMode::Exclude, Dtk::Addons::VisualEffect::ChannelSplitDirection direction = Dtk::Addons::VisualEffect::ChannelSplitDirection::Left, int padding = 5);

/**
 * @brief Apply the QGraphicsEffect you want
 * @param src
 * @param effect
 * @param extent
 * @return Image with applyed effects
 */
QImage applyEffectToImage(QImage src, QGraphicsEffect *effect, int extent = 0);

/**
 * @brief GS Image binding
 * @param src
 * @return Image in gray scale without alpha (255)
 */
QImage bindToGS(QImage src);

/**
 * @brief GSA Image binding
 * @param src
 * @return Image in gray scale with alpha (source dependent)
 */
QImage bindToGSA(QImage src);

/**
 * @brief Image blur then channel split: channel blending!
 * @param src
 * @param channel
 * @param mode
 * @param radius
 * @return Image with applyed settings for channels options
 */
QImage blendChannel(QImage src, int channel = Dtk::Addons::VisualEffect::ColorChannel::Red, Dtk::Addons::VisualEffect::ChannelSplitMode mode = Dtk::Addons::VisualEffect::ChannelSplitMode::Exclude, int radius = 5);

#endif // GRAPHICTOOLS_H
