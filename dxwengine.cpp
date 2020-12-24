#include "dxwengine.h"

PageWidget::PageWidget() : Widget() {}

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
        return w;
    } else {
        return XWEngine::generateInstance(elementType, args);
    }
}
