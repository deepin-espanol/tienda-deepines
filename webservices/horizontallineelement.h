#ifndef HORIZONTALLINEELEMENT_H
#define HORIZONTALLINEELEMENT_H

#include "ext/libda-release/abstractelement.h"

#include <QFrame>

LDA_USE_NAMESPACE

/**
 * @brief Horizontal line XWE UI Element
 */
class HorizontalLineElement : public QFrame, public AbstractElement
{
    Q_OBJECT
public:
    explicit HorizontalLineElement();
    QObject *self() override;
    virtual void addElement(AbstractElement *element) override;
};

#endif // HORIZONTALLINEELEMENT_H
