#ifndef FILLERELEMENT_H
#define FILLERELEMENT_H

#include "ext/libda-release/basicelements.h"

LDA_USE_NAMESPACE

class FillerElement : public Widget
{
public:
    explicit FillerElement();

protected:
    void paintEvent(QPaintEvent *) override;
};

#endif // FILLERELEMENT_H
