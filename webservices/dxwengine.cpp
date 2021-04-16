#include "dxwengine.h"

#include "commontools/commonstorage.h"

#include "webservices/iconlist.h"
#include "webservices/bannerelement.h"
#include "webservices/horizontallineelement.h"
#include "webservices/headerlabel.h"
#include "webservices/coverlist.h"
#include "webservices/spacers.h"
#include "webservices/iconelement.h"
#include "webservices/labeladdon.h"
#include "webservices/fillerelement.h"

PageWidget::PageWidget() : QScrollArea(), AbstractElement(), AbstractHistoryHandler()
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    container = new QWidget;
    container->setContentsMargins(0, 0, 0, 5);
    container->setAutoFillBackground(true);
    this->setWidget(container);
    this->setWidgetResizable(true);
}

void PageWidget::load(QString)
{
    wmgr->fillTop(true);
    wmgr->fillBottom(true);
    wmgr->blurTop(true);
}

void PageWidget::resizeEvent(QResizeEvent *e)
{
    QFrame::resizeEvent(e);
    container->setFixedWidth(width());
}

void PageWidget::addElement(AbstractElement *element)
{
    if (element != nullptr) {
        if (QLayout *lay = qobject_cast<QLayout *>(element->self())) {
            container->setLayout(lay);
        } else {
            element->self()->setParent(container);
        }
    }
}

DXWEngine::DXWEngine(QObject *p) : XWEngine(p) {}
DXWEngine::~DXWEngine()
{
    this->XWEngine::~XWEngine();
}

AbstractElement *DXWEngine::generateInstance(QString elementType, QString args)
{
    if (elementType == "Page") {
        PageWidget *w = new PageWidget;
        if (args.contains("show()")) {
            w->show();
        }
        allElements << w;
    } else if (elementType == "Banner") {
        allElements << new BannerElement;
    } else if (elementType == "CoverList") {
        allElements << new CoverList;
    } else if (elementType == "CoverListItem") {
        allElements << new CoverListItem;
    } else if (elementType == "HorizontalLine") {
        allElements << new HorizontalLineElement;
    } else if (elementType == "IconListItem") {
        allElements << new IconListItem;
    } else if (elementType == "IconList") {
        allElements << new IconList;
    } else if (elementType == "Icon") {
        allElements << new IconElement;
    } else if (elementType == "HeaderLabel") {
        allElements << new HeaderLabel;
    } else if (elementType == "HSpacer") {
        allElements << new HSpacer;
    } else if (elementType == "VSpacer") {
        allElements << new VSpacer;
    } else if (elementType == "Label") {
        allElements << new LabelAddon;
    } else if (elementType == "Filler") {
        allElements << new FillerElement;
    } else {
        allElements << XWEngine::generateInstance(elementType, args);
    }
    return allElements.last();
}

void DXWEngine::destroyAllElements()
{
    while (allElements.length() != 0) {
        AbstractElement *e = allElements.at(0);
        allElements.removeAt(0);
        delete e;
        e->~AbstractElement();
    }
}
