#ifndef INDRAGGABLEWIDGET_H
#define INDRAGGABLEWIDGET_H

#include "libda_global.h"
#include <QWidget>

LDA_BEGIN_NAMESPACE

class LIBDA_SHARED_EXPORT InDraggableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InDraggableWidget(QWidget *parent = nullptr);
    bool isRaisingEnabled();

Q_SIGNALS:
    void dragEnded();
    void dragStarted();

public Q_SLOTS:
    void enableRaising(bool enable = true);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *e) override;

    virtual void hoverEnterEvent(QHoverEvent *e);
    virtual void hoverLeaveEvent(QHoverEvent *e);
    virtual void hoverMoveEvent(QHoverEvent *e);

    bool event(QEvent *e) override;

private:
    bool holding = false;
    bool autoRaise = false;
    int m_x = 0;
    int m_y = 0;
};

LDA_END_NAMESPACE

#endif // INDRAGGABLEWIDGET_H
