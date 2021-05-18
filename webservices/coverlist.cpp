#include "coverlist.h"

#include "webservices/erh.h"
#include "webservices/pathmaker.h"
#include "webservices/iconlist.h"
#include "webservices/dynamicressourceloader.h"
#include "commontools/imagery.h"

#include <QImageReader>
#include <QPainter>
#include <QPixmap>
#include <QPainterPath>
#include <QStyledItemDelegate>

#include <QMouseEvent>

#include <iostream>

#define ITEM_HEIGHT 150
#define ITEM_WIDTH 200
#define ITEM_SPACING 5

struct Delegate: public QStyledItemDelegate
{
public:
    REFF *refs = nullptr;

    Delegate(QObject *parent = nullptr) : QStyledItemDelegate(parent)
    {
    }

    void paint(QPainter *p, const QStyleOptionViewItem &option, const QModelIndex &idx) const override
    {
        int bx = option.rect.x();
        int by = option.rect.y();
        CoverListItem *src = refs->value(idx.data().toString());
        QPoint srcP = p->brushOrigin();

        p->save();
        p->setRenderHint(QPainter::Antialiasing);

        //Restrain the painting area.
        QPainterPath area;
        area.addRoundedRect(QRect(bx, by, ITEM_WIDTH, ITEM_HEIGHT), 5, 5);
        p->setClipPath(area);
        //If we don't set the origin, the image painting become.. eh
        p->setBrushOrigin(QPoint(bx, by));

        //Some checks have to be done here...
        if (!src->hasLoaded) {
            src->setText(src->m_name);
        }

        QBrush b;
        if(option.state & QStyle::State_MouseOver) {
            b = QBrush(src->blurred.scaled(ITEM_WIDTH, ITEM_HEIGHT, Qt::KeepAspectRatioByExpanding));
        } else {
            b = QBrush(src->img.scaled(ITEM_WIDTH, ITEM_HEIGHT, Qt::KeepAspectRatioByExpanding));
        }
        p->setBrush(b);
        p->setPen(QPen(Qt::transparent, 0));
        p->drawRoundedRect(bx, by, ITEM_WIDTH, ITEM_HEIGHT, 5, 5);

        p->setBrush(QBrush());

        //Put the text
        QFont f = QFont();
        f.setBold(true);
        f.setWeight(60);
        f.setPixelSize(33);
        p->setFont(f);

        // get the data from the index
        QString title  = idx.data().toString();

        //Paint the text, and replace, if needed, the last chars to have something like "brave-brow..."
        QFontMetrics metrics(p->font());
        int len = metrics.horizontalAdvance(title);

        bool shouldCut = false;
        while (len > (ITEM_WIDTH - (ITEM_SPACING*2))) {
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

        //The text H pos
        int cy = by+(ITEM_HEIGHT - (metrics.height()/2));

        //Put the text BG first
        QColor c = QPalette().color(QPalette::ColorGroup::Current, QPalette::ColorRole::Base);
        c.setAlpha(100);
        p->fillRect(QRect(bx, cy-20, ITEM_WIDTH, ITEM_HEIGHT-cy+40), c);

        //Put the text
        p->setPen(QPalette().color(QPalette::ColorGroup::Current, QPalette::ColorRole::Text));
        p->drawText(QPoint(bx+((ITEM_WIDTH - len)/2), cy+10), title);

        //Reset
        p->setBrushOrigin(srcP);
        p->restore();
    }

    QSize sizeHint(const QStyleOptionViewItem &, const QModelIndex &) const override
    {
        return QSize(ITEM_WIDTH, ITEM_HEIGHT);
    }
};

CoverList::CoverList() : QListWidget(), AbstractElement()
{
    delegate = new Delegate;
    this->references = new REFF();
    delegate->refs = this->references;
    setItemDelegate(delegate);
    setViewport(new ViewPort);
    setFlow(Flow::LeftToRight);
    //setSpacing(150);
    setFrameShape(QFrame::Shape::NoFrame);
    setFixedHeight(ITEM_HEIGHT + 18);
    setSpacing(ITEM_SPACING);
    viewport()->setAttribute(Qt::WA_Hover);
}

void CoverList::addElement(AbstractElement *element)
{
    if(CoverListItem *src = dynamic_cast<CoverListItem *>(element)) {
        src->setParent(this);
        addItem(new QListWidgetItem(src->m_name));
        delegate->refs->insert(src->m_name, src);
    }
}

CoverListItem::CoverListItem() : QObject(nullptr), AbstractElement()
{
}

void CoverListItem::handleResponse(QString p)
{
    if (!p.isEmpty()) {
        img.load(p);
    } else {
        img.load(":/images/default-cover.jpg");
    }
    //Scaling makes it use less mem space, and fix blur issues that we can have when the images have not the same sizes
    img = img.scaled(ITEM_WIDTH, ITEM_HEIGHT);
    //A first one, then a second one. The first is the strong blur, that leaves pixels visible while the 2nd one is to erase these ugly pixels.
    blurred = blur(blur(img, img.rect(), 6), img.rect(), 4);
}

void CoverListItem::setText(QString t)
{
    hasLoaded = true;
    connect(DynamicResourceLoader::instance()->loadRs(PathMaker::getUrl(t, ImageType::Cover)),
            &DynamicResource::finished,
            this,
            &CoverListItem::handleResponse
           );
    m_name = t;
    Q_EMIT textChanged(t);
}
