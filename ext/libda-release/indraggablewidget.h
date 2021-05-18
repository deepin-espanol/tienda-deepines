#ifndef INDRAGGABLEWIDGET_H
#define INDRAGGABLEWIDGET_H

#include "libda_global.h"
#include <QWidget>

LDA_BEGIN_NAMESPACE

/**
 * @brief Draggable widget placed inside another widget (the parent).
 */
class LIBDA_SHARED_EXPORT InDraggableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InDraggableWidget(QWidget *parent = nullptr);
    /**
     * @brief Whether it should go to parent's widget top stack.
     * @return
     */
    bool isRaisingEnabled();

Q_SIGNALS:
    /**
     * @brief User clicked on it to drag.
     */
    void dragEnded();
    /**
     * @brief User ended click to stop drag.
     */
    void dragStarted();

public Q_SLOTS:
    /**
     * @brief Must go to parent's top stack, in front of other widgets.
     * @param enable
     */
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
