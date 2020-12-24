#include "dxwengine.h"

PageWidget::PageWidget() : Widget(), AbstractHistoryHandler() {}

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
        return w;
    } else {
        AbstractElement *e = XWEngine::generateInstance(elementType, args);
        allElements << e;
        return e;
    }
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
