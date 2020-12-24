#ifndef STACKEDSLIDEWIDGET_H
#define STACKEDSLIDEWIDGET_H

#include "libda_global.h"
#include "touchinterfacing.h"

#include <QStackedWidget>

LDA_BEGIN_NAMESPACE

class LIBDA_SHARED_EXPORT StackedSlideWidget : public QStackedWidget, public TouchInterfacing
{
    Q_OBJECT
public:
    explicit StackedSlideWidget(QWidget *parent = nullptr);
    ~StackedSlideWidget() override;
    bool handleSwipeGesture(SwipingGesture *gesture) override;

protected:
    bool handleOtherEvents(QEvent *event) override;
    void paintEvent(QPaintEvent *) override;
};

LDA_END_NAMESPACE

#endif // STACKEDSLIDEWIDGET_H
