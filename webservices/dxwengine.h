#ifndef DXWENGINE_H
#define DXWENGINE_H

#include "commontools/historymanager.h"
#include "webservices/layouts.h"

#include <QScrollArea>
#include "ext/libda-release/xwengine.h"
#include "ext/libda-release/basicelements.h"

LDA_USE_NAMESPACE

/**
 * @brief Class to wrap web content integration over XWE
 */
class PageWidget : public QScrollArea, public AbstractElement, public AbstractHistoryHandler
{
    Q_OBJECT
public:
    explicit PageWidget();
    inline virtual QObject *self() override {return this;}
    inline virtual AbstractHistoryHandler *ahh() {return this;}
    inline virtual QWidget *widget() const override {return container;}
    virtual void load(QString) override;
    virtual void unload() override;
    virtual void addElement(AbstractElement *element) override;

protected:
    void resizeEvent(QResizeEvent *e) override;

private:
    QWidget *container;
    VLayout *main_layout;
};

/**
 * @brief Class to wrap errors while the web content load fails
 */
class FallBackPage : public PageWidget
{
};

/**
 * @brief Our own XWEngine to add element types
 */
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
