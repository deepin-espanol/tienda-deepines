#include "labeladdon.h"

#include <QMetaEnum>

LabelAddon::LabelAddon() : Label() {}

void LabelAddon::setAlign(QString align)
{
    setAlignment(static_cast<Qt::AlignmentFlag>(QMetaEnum::fromType<Translated>().keyToValue(align.toLocal8Bit())));
    Q_EMIT alignChanged(this->align());
}

QString LabelAddon::align()
{
    return QMetaEnum::fromType<Translated>().key(static_cast<int>(alignment()));
}
