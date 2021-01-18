#include "bigprogressor.h"

#include <QHBoxLayout>

BigProgressor::BigProgressor() : QWidget(), AnimatorElement()
{
    QHBoxLayout *lay = new QHBoxLayout;
    QVBoxLayout *head = new QVBoxLayout;

    titlebar.setMaximumHeight(30);

    lay->addWidget(&titlebar);
    lay->addLayout(head);
    lay->addWidget(&pad);
    lay->addWidget(&message);

    pad.setFixedSize(200, 200);

    setMaximumHeight(200);
}

void BigProgressor::runAnim()
{
    pad.startAnimation();
}

CircleProgressAnimatePad &BigProgressor::getPad()
{
    return pad;
}

void BigProgressor::setTitle(QString t)
{
    titlebar.setText(t);
}

void BigProgressor::setMessage(QString msg)
{
    message.setText(msg);
}

void BigProgressor::setPercentage(double percentage)
{
    pad.setCurrentValue(percentage);
}

void BigProgressor::setTitleBarVisible(bool v)
{
    titlebar.setVisible(v);
}

void BigProgressor::setInProgressBarValueVisible(bool v)
{
    pad.setMiddleTextVisible(false);
}
