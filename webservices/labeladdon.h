#ifndef LABELADDON_H
#define LABELADDON_H

#include "ext/libda-release/basicelements.h"

LDA_USE_NAMESPACE

class LabelAddon : public Label
{
    Q_OBJECT
    Q_PROPERTY(QString align WRITE setAlign READ align NOTIFY alignChanged)

public:
    enum Translated {
        AlignLeft = 0x0001,
        AlignLeading = AlignLeft,
        AlignRight = 0x0002,
        AlignTrailing = AlignRight,
        AlignHCenter = 0x0004,
        AlignJustify = 0x0008,
        AlignAbsolute = 0x0010,
        AlignHorizontal_Mask = AlignLeft | AlignRight | AlignHCenter | AlignJustify | AlignAbsolute,

        AlignTop = 0x0020,
        AlignBottom = 0x0040,
        AlignVCenter = 0x0080,
        AlignBaseline = 0x0100,
        // Note that 0x100 will clash with Qt::TextSingleLine = 0x100 due to what the comment above
        // this enum declaration states. However, since Qt::AlignBaseline is only used by layouts,
        // it doesn't make sense to pass Qt::AlignBaseline to QPainter::drawText(), so there
        // shouldn't really be any ambiguity between the two overlapping enum values.
        AlignVertical_Mask = AlignTop | AlignBottom | AlignVCenter | AlignBaseline,

        AlignCenter = AlignVCenter | AlignHCenter
    };
    Q_ENUM(Translated)

    explicit LabelAddon();
    Q_SIGNAL void alignChanged(QString align);
    Q_SLOT void setAlign(QString align);
    QString align();
};

#endif // LABELADDON_H
