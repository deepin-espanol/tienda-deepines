#ifndef VISUALSTACKELEMENT_H
#define VISUALSTACKELEMENT_H

#include "touchinterfacing.h"
#include <QStackedWidget>

LDA_BEGIN_NAMESPACE

class LIBDA_SHARED_EXPORT VisualStackElement : public QStackedWidget, public TouchInterfacing
{
    Q_OBJECT
public:
    explicit VisualStackElement(QWidget *parent = nullptr);
    ~VisualStackElement() override;
    bool handleSwipeGesture(SwipingGesture *gesture) override;

protected:
    bool handleOtherEvents(QEvent *event) override;
    void paintEvent(QPaintEvent *) override;
};

LDA_END_NAMESPACE

#endif // VISUALSTACKELEMENT_H
