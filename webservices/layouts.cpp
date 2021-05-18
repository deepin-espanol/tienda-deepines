#include "layouts.h"

HLayout::HLayout(QWidget *p) : Dtk::Addons::HBoxLayout(p) {}

QObject *HLayout::self() {return this;}

void HLayout::addElement(AbstractElement *e)
{
    return HBoxLayout::addElement(e);
}

void HLayout::setLeftMargin(int v)
{
    QMargins m = this->contentsMargins();
    setContentsMargins(v, m.top(), m.right(), m.bottom());
    //Q_EMIT leftMarginChanged(v);
}
void HLayout::setRightMargin(int v)
{
    QMargins m = this->contentsMargins();
    setContentsMargins(m.left(), m.top(), v, m.bottom());
    //Q_EMIT rightMarginChanged(v);
}
void HLayout::setTopMargin(int v)
{
    QMargins m = this->contentsMargins();
    setContentsMargins(m.left(), v, m.right(), m.bottom());
    //Q_EMIT topMarginChanged(v);
}
void HLayout::setBottomMargin(int v)
{
    QMargins m = this->contentsMargins();
    setContentsMargins(m.left(), m.top(), m.right(), v);
    //Q_EMIT bottomMarginChanged(v);
}

int HLayout::leftMargin()
{
    return contentsMargins().left();
}
int HLayout::rightMargin()
{
    return contentsMargins().right();
}
int HLayout::topMargin()
{
    return contentsMargins().top();
}
int HLayout::bottomMargin()
{
    return contentsMargins().bottom();
}


VLayout::VLayout(QWidget *p) : Dtk::Addons::VBoxLayout(p) {}

QObject *VLayout::self() {return this;}

void VLayout::addElement(AbstractElement *e)
{
    return VBoxLayout::addElement(e);
}

void VLayout::setLeftMargin(int v)
{
    QMargins m = this->contentsMargins();
    setContentsMargins(v, m.top(), m.right(), m.bottom());
    //Q_EMIT leftMarginChanged(v);
}
void VLayout::setRightMargin(int v)
{
    QMargins m = this->contentsMargins();
    setContentsMargins(m.left(), m.top(), v, m.bottom());
    //Q_EMIT rightMarginChanged(v);
}
void VLayout::setTopMargin(int v)
{
    QMargins m = this->contentsMargins();
    setContentsMargins(m.left(), v, m.right(), m.bottom());
    //Q_EMIT topMarginChanged(v);
}
void VLayout::setBottomMargin(int v)
{
    QMargins m = this->contentsMargins();
    setContentsMargins(m.left(), m.top(), m.right(), v);
    //Q_EMIT bottomMarginChanged(v);
}

int VLayout::leftMargin()
{
    return contentsMargins().left();
}
int VLayout::rightMargin()
{
    return contentsMargins().right();
}
int VLayout::topMargin()
{
    return contentsMargins().top();
}
int VLayout::bottomMargin()
{
    return contentsMargins().bottom();
}
