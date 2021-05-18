#include "iconlist.h"

#include "webservices/erh.h"

#include <QStyledItemDelegate>
#include <QPainterPath>
#include <QPainter>
#include <QIcon>
#include <QPixmap>
#include <QPaintEvent>

#define ITEM_HEIGHT 114
#define ITEM_WIDTH 96
#define IMAGE_SIZE 90
#define C_SPACING 2

struct MyDelegate: public QStyledItemDelegate
{
    MyDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter *p, const QStyleOptionViewItem &option, const QModelIndex &idx) const override
    {
        int bx = option.rect.x();
        int by = option.rect.y();
        p->save();

        // get the data from the index
        QString title  = idx.data().toString();
        QPixmap pixmap = QIcon::fromTheme(title).pixmap(QSize(IMAGE_SIZE, IMAGE_SIZE));

        QPainterPath path;
        path.addRoundRect(QRect(bx, by, ITEM_WIDTH, ITEM_HEIGHT), 5, 5);

        p->fillPath(path, QPalette().color(QPalette::ColorGroup::Current, QPalette::ColorRole::Base));
        p->drawPixmap(QRect(bx+((ITEM_WIDTH-IMAGE_SIZE)/2), by+C_SPACING, IMAGE_SIZE, IMAGE_SIZE), pixmap, QRect(0, 0, IMAGE_SIZE, IMAGE_SIZE));

        QFontMetrics metrics(p->font());
        int len = metrics.horizontalAdvance(title);

        bool shouldCut = false;
        while (len > (ITEM_WIDTH - (C_SPACING*2))) {
            if (!shouldCut) {
                shouldCut = true;
            }
            title.chop(1);
            len = metrics.horizontalAdvance(title);
        }

        if (shouldCut) {
            //We replace the 3 lasts by "..."
            title.chop(3);
            title.append("...");
            len = metrics.horizontalAdvance(title);
        }

        p->setPen(QPalette().color(QPalette::ColorGroup::Current, QPalette::ColorRole::Text));
        p->drawText(QPoint(bx+((ITEM_WIDTH - len)/2), by+(ITEM_HEIGHT - (metrics.height()/2))), title);

        p->restore();
    }

    QSize sizeHint(const QStyleOptionViewItem &, const QModelIndex &) const override
    {
        return QSize(ITEM_WIDTH, ITEM_HEIGHT);
    }
};

IconListItem::IconListItem() : QObject() {}

ViewPort::ViewPort() : QWidget() {}

IconList::IconList() : QListWidget(), AbstractElement()
{
    setItemDelegate(new MyDelegate());
    setViewport(new ViewPort);
    setFlow(Flow::LeftToRight);
    setSpacing(5);
    setFrameShape(QFrame::Shape::NoFrame);
    setFixedHeight(ITEM_HEIGHT + 13);
    connect(this, &QListWidget::itemClicked, this, [](QListWidgetItem *it) {
        ERH::instance()->generatePkgRequest(it->text());
    });
}

void IconList::addElement(AbstractElement *element)
{
    if(IconListItem *it = dynamic_cast<IconListItem *>(element)) {
        this->addItem(it->property("value").toString());
    }
}

void ViewPort::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    if (e->rect().contains(QRect(0, 0, 5, 5)) ||
        e->rect().contains(QRect(width()-5, 0, 5, 5)) ||
        e->rect().contains(QRect(0, height()-5, 5, 5)) ||
        e->rect().contains(QRect(width()-5, height()-5, 5, 5))
       ) {
        QPainterPath p;
        p.addRoundRect(this->rect(), 5, 5);
        painter.fillPath(p, QPalette().color(QPalette::ColorGroup::Current, QPalette::ColorRole::Window));
    } else {
        painter.fillRect(e->rect(), palette().color(QPalette::ColorGroup::Current, QPalette::ColorRole::Window));
    }
}
