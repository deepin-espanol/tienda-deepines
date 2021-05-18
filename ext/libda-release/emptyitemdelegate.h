#ifndef EMPTYITEMDELEGATE_H
#define EMPTYITEMDELEGATE_H

#include "libda_global.h"
#include <QItemDelegate>

LDA_BEGIN_NAMESPACE

/**
 * @brief Empty QItemDelegate, used when you have widgets and such, but you won't have any item painting.
 */
class LIBDA_SHARED_EXPORT EmptyItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit EmptyItemDelegate(QObject *parent = nullptr);
    ~EmptyItemDelegate();
    void paint(QPainter *, const QStyleOptionViewItem &, const QModelIndex &) const;
};

LDA_END_NAMESPACE

#endif // EMPTYITEMDELEGATE_H
