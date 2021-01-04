#include "splittedbutton.h"

#include <iostream>
#include <QResizeEvent>

DWIDGET_USE_NAMESPACE

SplittedButton::SplittedButton(QWidget *p) : DButtonBox(p)
{
    mainBtn = new DButtonBoxButton("", p);
    optionalBtn = new DButtonBoxButton(DStyle::SP_ArrowDown);

    setButtonList({mainBtn, optionalBtn}, false);
    connect(optionalBtn, &DButtonBoxButton::clicked, this, &SplittedButton::popupMenu);
}

SplittedButton::SplittedButton(QAction *act, QWidget *p) : SplittedButton(p)
{
    setDefaultAction(act);
}

SplittedButton::SplittedButton(QAction *act, QMenu *m, QWidget *p) : SplittedButton(act, p)
{
    setOptionalMenu(m);
}

void SplittedButton::resizeEvent(QResizeEvent *e)
{
    optionalBtn->setFixedWidth(e->size().height());
    DButtonBox::resizeEvent(e);
}

void SplittedButton::popupMenu()
{
    if (m_menu != nullptr) {
        m_menu->popup(mapToGlobal(this->rect().bottomLeft()));
    }
}

void SplittedButton::setDefaultAction(QAction *act)
{
    if (act != nullptr) {
        if (m_act != nullptr) {
            disconnect(mainBtn, &DButtonBoxButton::clicked, m_act, &QAction::triggered);
            disconnect(m_act, &QAction::changed, this, &SplittedButton::updateMainButton);
        }
        m_act = act;
        connect(mainBtn, &DButtonBoxButton::clicked, m_act, &QAction::triggered);
        connect(m_act, &QAction::changed, this, &SplittedButton::updateMainButton);
        updateMainButton();
    }
}

void SplittedButton::updateMainButton()
{
    mainBtn->setIcon(m_act->icon());
    mainBtn->setChecked(m_act->isChecked());
    mainBtn->setText(m_act->text());
    mainBtn->setToolTip(m_act->toolTip());
    mainBtn->setShortcut(m_act->shortcut());
}

void SplittedButton::setOptionalMenu(QMenu *m)
{
    if (m != nullptr) {
        m_menu = m;
    }
}

void SplittedButton::setMainButtonEnabled(bool en)
{
    mainBtn->setEnabled(en);
}

void SplittedButton::setOptionalButtonEnabled(bool en)
{
    optionalBtn->setEnabled(en);
}
