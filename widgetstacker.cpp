#include "widgetstacker.h"

#include <QEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QApplication>

#include <iostream>

WidgetStacker::WidgetStacker(QWidget *parent) : QWidget(parent) {}

QWidget *WidgetStacker::currentWidget()
{
    return currWidget;
}

QList<QWidget *> WidgetStacker::widgets()
{
    return m_widgets;
}

void WidgetStacker::addWidget(QWidget *w)
{
    if (currWidget) {
        currWidget->setVisible(false);
    }
    currWidget = w;
    if (m_widgets.contains(w) == false) {
        m_widgets << w;
        w->setParent(this);
        w->setVisible(true);
    }

    Q_EMIT widgetChanged();
}

void WidgetStacker::setCurrentWidget(QWidget *w)
{
    if (m_widgets.contains(w) && currWidget != w) {
        if (currWidget) {
            currWidget->setVisible(false);
        }
        currWidget = w;
        w->setVisible(true);
        currWidget->resize(this->size());
        repaint();
        Q_EMIT widgetChanged();
    }
}

bool WidgetStacker::eventFilter(QObject *src, QEvent *e)
{
    /* How to handle the painting of children and parent in this widget:
     * 1. Process event (A)
     * 2. Repaint child (A)
     *      3. Process event (B)
     *      4. Do nothing with it to let the child update it's own painting (B)
     * 4. Update painting (A)
     * 5. Paint the image rect that have been updated
     */
    if (paintCalled) {
        std::cout << "child painting" << std::endl;
        paintCalled = false;
        return false;
    } else if (e->type() == QEvent::Type::Paint && src == currWidget) {
        if (currWidget) {
            std::cout << "parent painting" << std::endl;
            QPaintEvent *p = static_cast<QPaintEvent *>(e);
            paintCalled = true;
            qApp->sendEvent(src, e);
            repaint(p->rect());
        }
        return true;
    }
    return false;
}

void WidgetStacker::paintEvent(QPaintEvent *e)
{
    /*if (currWidget) {
        QPainter().drawPixmap(e->rect(), currWidget->grab(e->rect()), e->rect());
    }*/
}

void WidgetStacker::resizeEvent(QResizeEvent *e)
{
    if (currWidget) {
        currWidget->resize(e->size());
    }
}
