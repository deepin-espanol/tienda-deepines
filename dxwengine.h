#ifndef DXWENGINE_H
#define DXWENGINE_H

#include "abstracthistoryhandler.h"

#include "xwengine.h"
#include "basicelements.h"

LDA_USE_NAMESPACE

class PageWidget : public Widget, public AbstractHistoryHandler
{
    Q_OBJECT
public:
    explicit PageWidget();
    inline virtual QObject *self() override {return this;}
    inline virtual AbstractHistoryHandler *ahh() {return this;}
    inline virtual QWidget *widget() const override {return (QWidget*)this;}
    inline virtual void load(QString) override {}
};

class DXWEngine : public XWEngine
{
public:
    DXWEngine(QObject *parent = nullptr);
    ~DXWEngine() override;
    virtual AbstractElement *generateInstance(QString elementType, QString args) override;
    void destroyAllElements();

private:
    QList<AbstractElement*> allElements;
};

#endif // DXWENGINE_H
