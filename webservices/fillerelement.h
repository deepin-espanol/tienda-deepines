#ifndef FILLERELEMENT_H
#define FILLERELEMENT_H

#include "ext/libda-release/basicelements.h"

#include <QSpacerItem>
#include <QObject>

LDA_USE_NAMESPACE

class FillerElement : public QSpacerItem, public AbstractElement
{
public:
    explicit FillerElement();

    QObject *self() override;
    void addElement(AbstractElement *element) override;
};

#endif // FILLERELEMENT_H
