#ifndef DRAGVIEW_H
#define DRAGVIEW_H

#include "historymanager.h"

#include <QFrame>
#include <DFileDragClient>
#include <QVBoxLayout>
#include <QUrl>
#include <QLabel>
#include <QLineEdit>

namespace Dtk {
namespace Addons {
class DynamicSvgParser;
}
namespace Widget {
class DLineEdit;
class DIconButton;
}
}

class QPushButton;

/**
 * @brief File drop QFrame
 */
class DropArea : public QFrame
{
    Q_OBJECT
public:
    DropArea(QWidget *parent = nullptr);
    Dtk::Widget::DLineEdit *le;

    void runChildFiltering();
Q_SIGNALS:
    void droped(QUrl u);
protected:
    bool eventFilter(QObject *o, QEvent *e) override;
    void dragEnterEvent(QDragEnterEvent *e) override;
    void dragMoveEvent(QDragMoveEvent *e) override;
    void dropEvent(QDropEvent *e) override;
};

/**
 * @brief The OFV, view to load from local file a PKG
 */
class OpenFileView : public DropArea, public AbstractHistoryHandler
{
    Q_OBJECT
public:
    explicit OpenFileView(QWidget *p = nullptr);
    void load(QString);
    inline QWidget *widget() const {return (QWidget*)this;}

protected Q_SLOTS:
    void handleFOP();
    void handleFU(QUrl u);

private:
    QLabel *lb;
    QLabel *icon;
    Dtk::Widget::DLineEdit *le;
    Dtk::Addons::DynamicSvgParser *parser;
    QHBoxLayout *hb;
    Dtk::Widget::DIconButton *next;
    QPushButton *btn;
    QVBoxLayout *lay;
};

#endif // DRAGVIEW_H
