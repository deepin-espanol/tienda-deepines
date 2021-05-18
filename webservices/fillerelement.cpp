#include "fillerelement.h"

FillerElement::FillerElement() : QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding),
    AbstractElement()
{
}

QObject *FillerElement::self()
{
    return nullptr;
}

void FillerElement::addElement(AbstractElement *) {}
