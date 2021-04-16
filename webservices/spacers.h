#ifndef SPACERS_H
#define SPACERS_H

#include "ext/libda-release/abstractelement.h"
#include <QSpacerItem>

LDA_USE_NAMESPACE

class HSpacer : public QSpacerItem, public AbstractElement
{
public:
    explicit HSpacer();
    inline QObject *self() override {return nullptr;}
    inline void addElement(AbstractElement *) override {}
};

class VSpacer : public QSpacerItem, public AbstractElement
{
public:
    explicit VSpacer();
    inline QObject *self() override {return nullptr;}
    inline void addElement(AbstractElement *) override {}
};


#endif // SPACERS_H
