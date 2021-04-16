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

#define ITEM_HEIGHT 150
#define ITEM_WIDTH 200

struct MyDelegate: public QStyledItemDelegate
{
    MyDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter *, const QStyleOptionViewItem &, const QModelIndex &) const override {}

    QSize sizeHint(const QStyleOptionViewItem &, const QModelIndex &) const override
    {
        return QSize(ITEM_WIDTH, ITEM_HEIGHT);
    }
};

CoverList::CoverList() : QListWidget(), AbstractElement()
{
    setItemDelegate(new MyDelegate);
    setViewport(new ViewPort);
    setFlow(Flow::LeftToRight);
    setSpacing(150);
    setFrameShape(QFrame::Shape::NoFrame);
    setFixedHeight(ITEM_HEIGHT + 18);
}

void CoverList::addElement(AbstractElement *element)
{
    if(CoverListItem *src = dynamic_cast<CoverListItem *>(element)) {
        QListWidgetItem *it = new QListWidgetItem;
        src->setParent(this);
        it->setSizeHint(src->sizeHint());
        addItem(it);
        setItemWidget(it, src);
    }
}

CoverListItem::CoverListItem() : Widget()
{
    setFixedSize(200, 150);
}

void CoverListItem::handleResponse(QString p)
{
    if (!p.isEmpty()) {
        img.load(p);
    } else {
        img.load(":/images/default-cover.jpg");
    }
    blurred = blur(img, img.rect(), 4);
    repaint();
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
    repaint();
    Q_EMIT textChanged(t);
}

void CoverListItem::enterEvent(QEvent *e)
{
    hovered = true;
    QWidget::enterEvent(e);
    repaint();
}

void CoverListItem::leaveEvent(QEvent *e)
{
    hovered = false;
    QWidget::leaveEvent(e);
    repaint();
}

void CoverListItem::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::MouseButton::LeftButton) {
        ERH::instance()->generatePkgRequest(m_name);
    }
}

void CoverListItem::paintEvent(QPaintEvent *)
{
    if (!hasLoaded) {
        setText(m_name);
    }
    QPainter paint(this);
    paint.setRenderHint(QPainter::Antialiasing);

    if (hovered) {
        paint.setBrush(QBrush(blurred.scaled(width(), height(), Qt::KeepAspectRatioByExpanding)));
    } else {
        paint.setBrush(QBrush(img.scaled(width(), height(), Qt::KeepAspectRatioByExpanding)));
    }
    paint.drawRoundedRect(0, 0, width(), height(), 5, 5);

    //Put the text
    QFont f = this->font();
    f.setBold(true);
    f.setWeight(60);
    f.setPixelSize(33);

    paint.setPen(QPalette().color(QPalette::ColorGroup::Current, QPalette::ColorRole::Text));
    paint.setFont(f);
    paint.drawText(QPoint(5, QFontMetrics(f).height()/2+5), m_name);
}
