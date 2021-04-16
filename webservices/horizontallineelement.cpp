#include "horizontallineelement.h"

#include <QLayout>

HorizontalLineElement::HorizontalLineElement() : QFrame(), AbstractElement()
{
    setObjectName(QString::fromUtf8("line"));
    setFrameShape(QFrame::HLine);
    setFrameShadow(QFrame::Sunken);
    setFixedHeight(3);
    setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
}

QObject *HorizontalLineElement::self() {return this;}

void HorizontalLineElement::addElement(AbstractElement *element)
{
    if (element != nullptr) {
        if (QLayout *lay = qobject_cast<QLayout *>(element->self())) {
            this->setLayout(lay);
        } else {
            element->self()->setParent(this);
        }
    }
}
