#ifndef BIGPROGRESSOR_H
#define BIGPROGRESSOR_H

#include "circleprogressanimatepad.h"
#include "animatorloader.h"

#include <QWidget>
#include <QLabel>

class BigProgressor : public QWidget, public AnimatorElement
{
    Q_OBJECT
public:
    explicit BigProgressor();
    CircleProgressAnimatePad &getPad();

    virtual void runAnim() override;

    operator QWidget &() {return *this;}
    operator QWidget *() {return this;}
    operator AnimatorElement &() {return *this;}
    operator AnimatorElement *() {return this;}

public Q_SLOTS:
    void setTitle(QString title);
    void setTitleBarVisible(bool visible = true);
    void setPercentage(double percentage);
    void setMessage(QString msg);
    void setInProgressBarValueVisible(bool visible = true);

private:
    QLabel titlebar;
    QLabel message;
    CircleProgressAnimatePad pad;
};

#endif // BIGPROGRESSOR_H
