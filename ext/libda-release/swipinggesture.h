#ifndef SWIPINGGESTURE_H
#define SWIPINGGESTURE_H

#include "libda_global.h"
#include <QGesture>

LDA_BEGIN_NAMESPACE

class LIBDA_SHARED_EXPORT SwipingGesture : public QSwipeGesture
{
    Q_OBJECT
public:
    explicit SwipingGesture(QSwipeGesture *event);
    SwipingGesture(QObject *parent = nullptr);

    Qt::GestureState state() const;
    QSwipeGesture::SwipeDirection horizontalDirection() const;
    QSwipeGesture::SwipeDirection verticalDirection() const;

    void setHorizontalDirection(QSwipeGesture::SwipeDirection);
    void setVerticalDirection(QSwipeGesture::SwipeDirection);
    void setGestureState(Qt::GestureState state);

private:
    bool usingInState = false;
    Qt::GestureState m_state = Qt::GestureState::NoGesture;
    QSwipeGesture::SwipeDirection m_horiz = QSwipeGesture::SwipeDirection::NoDirection;
    QSwipeGesture::SwipeDirection m_vert = QSwipeGesture::SwipeDirection::NoDirection;
};

LDA_END_NAMESPACE

#endif // SWIPINGGESTURE_H
