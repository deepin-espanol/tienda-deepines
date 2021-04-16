#include "bottompackagewidgetinformations.h"

#include <iostream>

#include <QFont>
#include <QPainter>
#include <QPainterPath>
#include <QColor>
#include <QPaintEvent>
#include <QFontMetrics>
#include <QPalette>

int VirtualField::reducedWidth()
{
    if (text != "") {
        QFontMetrics m2(*font2);
        return m2.width(text) + 4*padding + 4;
    }
    return 0;
}

int VirtualField::width()
{
    if (text != "") {
        QFontMetrics m1(*font1);
        QFontMetrics m2(*font2);
        return m1.width(descriptor) + m2.width(text) + 4*padding + 6;
    }
    return 0;
}

const QSize VirtualField::paintingSize()
{
    QFontMetrics m1(*font1);
    QFontMetrics m2(*font2);
    QSize size(m1.width(descriptor) + m2.width(text) + 4*padding + 6,
               m1.height() + 2*padding + 4);
    if (m1.height() < m2.height()) {
        size.setHeight(m2.height() + 2 *padding + 4);
    }
    return size;
}

const QSize VirtualField::reducedPaintingSize()
{
    QFontMetrics m2(*font2);
    QSize size(m2.width(text) + 4*padding + 4,
               m2.height() + 2*padding + 4);
    return size;
}

void VirtualField::generatePainting(QPainter &p, QPoint sourcePoint, bool reduced)
{
    QPainterPath path;
    //std::cout << "value: " << descriptor.toLocal8Bit().data() << std::endl;
    if (text != "") {
        if (reduced) {
            QSize sized = reducedPaintingSize();
            if (sized.width() > 0) {
                path.addRoundedRect(QRectF(sourcePoint.x(), sourcePoint.y(), sized.width() - padding, sized.height()), 10, 10);
                QPen pen(parent->palette().color(QPalette::ColorGroup::Current, QPalette::ColorRole::ButtonText), 2);
                p.setPen(pen);
                p.fillPath(path, parent->palette().color(QPalette::ColorGroup::Current, QPalette::ColorRole::Mid));
                p.drawPath(path);

                p.setPen(parent->palette().color(QPalette::ColorGroup::Current, QPalette::ColorRole::ButtonText));
                p.setFont(*font2);
                p.drawText(QPoint(sourcePoint.x() + padding*1.5, sourcePoint.y() - padding + (sized.height() + QFontMetrics(*font2).height())/2), text);
            }
        } else {
            QSize sized = paintingSize();
            if (sized.width() > 0) {
                path.addRoundedRect(QRectF(sourcePoint.x(), sourcePoint.y(), sized.width() - padding, sized.height()), 10, 10);
                QPen pen(parent->palette().color(QPalette::ColorGroup::Current, QPalette::ColorRole::ButtonText), 2);
                p.setPen(pen);
                p.fillPath(path, parent->palette().color(QPalette::ColorGroup::Current, QPalette::ColorRole::Mid));
                p.drawPath(path);

                int left = padding*2 + QFontMetrics(*font1).width(descriptor) + sourcePoint.x();
                p.drawLine(QLine(left, sourcePoint.y(), left, sourcePoint.y() + sized.height()));

                p.setFont(*font1);
                p.drawText(QPoint(sourcePoint.x() + padding, sourcePoint.y() - padding + (sized.height() + QFontMetrics(*font1).height())/2), descriptor);
                p.setFont(*font2);
                p.drawText(QPoint(left + padding*1.5, sourcePoint.y() - padding + (sized.height() + QFontMetrics(*font2).height())/2), text);
            }
        }
    }
}

BottomPackageWidgetInformations::BottomPackageWidgetInformations(QWidget *parent) : QWidget(parent)
{
    m_headerFont = this->font();
    m_headerFont.setPointSize(10);
    m_headerFont.setBold(true);
    m_dataFont = m_headerFont;
    m_dataFont.setBold(false);
}

QFont BottomPackageWidgetInformations::headerFont() {return m_headerFont;}
QFont BottomPackageWidgetInformations::dataFont() {return m_dataFont;}
void BottomPackageWidgetInformations::clear() {fields.clear(); update();}

void BottomPackageWidgetInformations::setDataFont(QFont f)
{
    int i = 0;
    while (i < fields.length()) {
        fields[i].font2 = &f;
        i++;
    }
    update();
}

void BottomPackageWidgetInformations::setHeaderFont(QFont f)
{
    int i = 0;
    while (i < fields.length()) {
        fields[i].font1 = &f;
        i++;
    }
    update();
}

void BottomPackageWidgetInformations::setData(QList<QString> d)
{
    int i = 0;
    while (i < fields.length()) {
        fields[i].text = d.at(i);
        i++;
    }
    update();
}

void BottomPackageWidgetInformations::setHeaders(QList<QString> h)
{
    int i = 0;
    while (i < h.length()) {
        VirtualField field;
        if (fields.count() <= i) {
            field.font1 = &m_headerFont;
            field.font2 = &m_dataFont;
            field.isEmpty = false;
            field.parent = this;
            field.descriptor = h.at(i);
            fields << field;
        } else {
            const_cast<VirtualField *>(&fields.at(i))->descriptor = h.at(i);;
        }
        i++;
    }

    if (fields.length() > i) {
        i--;
        while (fields.length() != i) {
            fields.removeAt(fields.count());
        }
    }
    update();
}

void BottomPackageWidgetInformations::resizeEvent(QResizeEvent *e)
{
    int maxW = spcaingMargin*2, i = 0;
    while (i < fields.length()) {
        maxW += const_cast<VirtualField *>(&fields.at(i))->paintingSize().width() + spcaingMargin;
        i++;
    }

    if (maxW > this->width()) {
        useCompacted = true;
    } else {
        useCompacted = false;
    }

    QWidget::resizeEvent(e);
}

void BottomPackageWidgetInformations::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.fillRect(this->rect(), palette().color(QPalette::ColorGroup::Current, QPalette::ColorRole::Base));

    if (!fields.isEmpty()) {
        int top = (this->height() - const_cast<VirtualField *>(&fields.at(0))->paintingSize().height() - 6)/2 + spcaingMargin*0.95;
        int currX = spcaingMargin;

        int i = 0;
        while (i < fields.length()) {
            const_cast<VirtualField *>(&fields.at(i))->generatePainting(p, QPoint(currX, top), useCompacted);
            if (useCompacted) {
                int v = const_cast<VirtualField *>(&fields.at(i))->reducedWidth();
                if (v > 0) {
                    currX += v;
                } else {
                    currX -= spcaingMargin;
                }
            } else {
                int v = const_cast<VirtualField *>(&fields.at(i))->width();
                if (v > 0) {
                    currX += v;
                } else {
                    currX -= spcaingMargin;
                }
            }
            currX += spcaingMargin;
            i++;
        }
    }
}
