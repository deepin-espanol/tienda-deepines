#include "dragview.h"

#include "commonstorage.h"

#include "ext/libda-release/dynamicsvgparser.h"

#include <DButtonBox>
#include <DPushButton>
#include <DIconButton>
#include <QDragEnterEvent>
#include <QProgressBar>
#include <QMimeData>
#include <DFileDialog>
#include <iostream>

static QProgressBar *p;

DGUI_USE_NAMESPACE

static DFileDragClient *c;

DropArea::DropArea(QWidget *parent) : QFrame(parent)
{
    setFrameShape(Shape::NoFrame);
    setAcceptDrops(true);
}

void DropArea::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

void DropArea::dragMoveEvent(QDragMoveEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

void DropArea::dropEvent(QDropEvent *e)
{
    // check for our needed mime type, here a file or a list of files
    if (e->mimeData()->hasUrls())
    {
        e->acceptProposedAction();
        le->setText(e->mimeData()->urls().at(0).toLocalFile());
        Q_EMIT droped(e->mimeData()->urls().at(0).toLocalFile());
    }
}

bool DropArea::eventFilter(QObject *o, QEvent *e)
{
    if (qobject_cast<QWidget *>(o)) {
        if (e->type() == QEvent::Type::Drop) {
            if (e->type() == QEvent::DragMove) {
                this->dragMoveEvent(static_cast<QDragMoveEvent *>(e));
            } else if (e->type() == QEvent::DragEnter) {
                this->dragEnterEvent(static_cast<QDragEnterEvent *>(e));
            } else if (e->type() == QEvent::Drop) {
                this->dropEvent(static_cast<QDropEvent *>(e));
            } else {
                return o->event(e);
            }
        } else {
            return o->event(e);
        }
    }
    return true;
}

void DropArea::runChildFiltering()
{
    int max = layout()->count(), i = 0;
    while (i<max) {
        if (layout()->itemAt(i) != nullptr) {
            if (layout()->itemAt(i)->widget() != nullptr) {
                layout()->itemAt(i)->widget()->installEventFilter(this);
                layout()->itemAt(i)->widget()->setAcceptDrops(true);
            }
        }
        i++;
    }
}

void clearLayout(QLayout *layout) {
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
           delete item->widget();
        }
        delete item;
    }
}

OpenFileView::OpenFileView(QWidget *parent) : DropArea(parent),
    AbstractHistoryHandler(),
    lb(new QLabel(this)),
    icon(new QLabel(this)),
    le(new Dtk::Widget::DLineEdit(this)),
    next(new Dtk::Widget::DIconButton(DStyle::SP_ArrowEnter)),
    btn(new QPushButton(this)),
    lay(new QVBoxLayout(this))
{
    this->setLayout(lay);
    this->DropArea::le = this->le;

    QProgressBar *pp = new QProgressBar(storage->currentWindow);
    p = pp;
    p->setMinimum(0);
    p->setMaximum(100);
    p->setFixedHeight(20);
    p->setTextVisible(false);

    lb->setText(tr("Drag the file you want to install here"));
    lb->setAlignment(Qt::AlignmentFlag::AlignCenter);
    le->setPlaceholderText(tr("file.%1").arg("deb"));
    le->setRightWidgets({btn, next});
    next->setEnabled(false);
    btn->setIcon(QIcon::fromTheme("document-open"));

    QFile f(":/images/drop.svg");
    f.open(QIODevice::OpenModeFlag::ReadOnly);
    parser = new Dtk::Addons::DynamicSvgParser(f.readAll(), this->palette(), this);
    parser->setRenderedSize(QSize(190, 200));
    icon->setPixmap(*parser->result());
    icon->setAlignment(Qt::AlignCenter);

    clearLayout(this->layout());
    layout()->addWidget(lb);
    layout()->addWidget(icon);
    layout()->addWidget(le);

    runChildFiltering();

    connect(le, &DLineEdit::textEdited, this, &OpenFileView::handleFU);
    connect(this, &DropArea::droped, this, &OpenFileView::handleFU);
    connect(next, &QPushButton::clicked, this, &OpenFileView::handleFOP);
    connect(qApp, &QGuiApplication::paletteChanged, parser, &Dtk::Addons::DynamicSvgParser::setSource);
    connect(qApp, &QGuiApplication::paletteChanged, this, [this]() {this->icon->setPixmap(*parser->result());});
    connect(btn, &QPushButton::clicked, this, [this]() {
        QUrl u = Dtk::Widget::DFileDialog::getOpenFileUrl(this, tr("Open the package file"), QUrl("computer:///"), tr("Package files (*.%1)").arg("deb"));
        if (!u.isEmpty()) {
            le->setText(u.toString().remove(0, 7));//Remove the file:// of file:///my.file
            this->handleFU(u);
        }
    });
}

void OpenFileView::load(QString s)
{
    p->setVisible(true);
    wmgr->setBottom(p);
    wmgr->fillBottom(false);
    wmgr->fillTop(false);
    p->setAttribute(Qt::WA_TranslucentBackground, false);
    if (!s.isEmpty()) {
        handleFU(QUrl(s));
    }
}

void OpenFileView::handleFOP()
{
    storage->hmgr->goTo("package-viewer:$file:"+le->text());
}

void OpenFileView::handleFU(QUrl u)
{
    if (!QFileInfo(u.toString()).exists() && !u.toString().endsWith(".deb")) {
        le->setAlert(true);
        le->showAlertMessage(tr("Fichier inexistant"), 2000);
        next->setDisabled(true);
    } else {
        le->setAlert(false);
        next->setDisabled(false);
    }
}
