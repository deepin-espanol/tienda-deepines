#include "fillerelement.h"

FillerElement::FillerElement() : Widget()
{
    setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
}

void FillerElement::paintEvent(QPaintEvent *) {}
