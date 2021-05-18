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
#include "webservices/videoplayer.h"

#include <QVBoxLayout>
#include <QMetaObject>
#include <QResizeEvent>

PageWidget::PageWidget() : QScrollArea(), AbstractElement(), AbstractHistoryHandler()
{
    container = new QWidget(this);
    container->setContentsMargins(0, 0, 0, 0);
    container->setAutoFillBackground(true);

    this->setWidget(container);
    this->setWidgetResizable(true);
    this->setAutoFillBackground(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

    main_layout = new VLayout(container);
    main_layout->setSpacing(0);
    main_layout->setMargin(0);
}

void PageWidget::load(QString)
{
    wmgr->fillTop(true);
    wmgr->fillBottom(true);
    wmgr->blurTop(true);
}

void PageWidget::unload()
{
    wmgr->fillTop(false);
    wmgr->fillBottom(true);
    wmgr->blurTop(false);
}

void PageWidget::resizeEvent(QResizeEvent *e)
{
    QScrollArea::resizeEvent(e);
    container->setFixedWidth(e->size().width());
    std::cout << "Resized!" << std::endl;
}

void PageWidget::addElement(AbstractElement *element)
{
    return main_layout->addElement(element);
    /*if (element) {
        if (QLayout *lay = qobject_cast<QLayout *>(element->self())) {
            //lay->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
            container->setLayout(lay);
        } else {
            element->self()->setParent(container);
        }
    }*/
}

DXWEngine::DXWEngine(QObject *p) : XWEngine(p)
{
    enableAppEvents = true;
    enableAutoParenting = true;
    enableObjectParenting = false;

    allElements = QList<AbstractElement *>();
}

DXWEngine::~DXWEngine()
{
    this->XWEngine::~XWEngine();
}

AbstractElement *DXWEngine::generateInstance(QString elementType, QString args)
{
    if (elementType == "Page") {
        allElements << new PageWidget;
    } else if (elementType == "Banner") {
        allElements << new BannerElement;
    } else if (elementType == "CoverList") {
        allElements << new CoverList;
    } else if (elementType == "CoverListItem") {
        allElements << new CoverListItem();
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
    } else if (elementType == "HLayout") {
        allElements << new HLayout;
    } else if (elementType == "VLayout") {
        allElements << new VLayout;
    /*} else if (elementType == "Player") {//DO NOT SUPPORT VP, IT IS BUGGY!! (due to the way it gets painted)
        allElements << new VideoPlayer;
    } else {*/
    } else {
        allElements << XWEngine::generateInstance(elementType, args);
    }

    if (args.contains("show()") && allElements.last() != nullptr && allElements.last()->self() != nullptr) {
        QMetaObject::invokeMethod(allElements.last()->self(), "show", Qt::DirectConnection);
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
