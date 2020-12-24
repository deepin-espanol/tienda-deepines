#ifndef DXWENGINE_H
#define DXWENGINE_H

#include "abstracthistoryhandler.h"

#include "xwengine.h"
#include "basicelements.h"

LDA_USE_NAMESPACE

class PageWidget : public Widget, AbstractHistoryHandler
{
    Q_OBJECT
public:
    PageWidget();
    inline virtual QWidget *self() override {return this;}
    inline virtual void load(QString) override {}
};

class DXWEngine : public XWEngine
{
public:
    DXWEngine(QObject *parent = nullptr);
    ~DXWEngine() override;
    virtual AbstractElement *generateInstance(QString elementType, QString args) override;
};

#endif // DXWENGINE_H
