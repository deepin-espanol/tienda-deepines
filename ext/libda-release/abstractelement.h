#ifndef ABSTRACTUIELEMENT_H
#define ABSTRACTUIELEMENT_H

#include "class_decl.h"
#include "libda_global.h"

#include <QObject>
#include <QMetaProperty>

#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>

LDA_BEGIN_NAMESPACE

class LIBDA_SHARED_EXPORT AbstractElement
{
public:
    AbstractElement();
    virtual ~AbstractElement();
    virtual QObject *self() = 0;
    virtual void addElement(AbstractElement *element) = 0;
    bool isSingletonClass();
    virtual AbstractElement *instance();

protected:
    bool m_singletonStatus = false;
};

LDA_END_NAMESPACE

#endif // ABSTRACTUIELEMENT_H
