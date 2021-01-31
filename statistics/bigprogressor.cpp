#include "bigprogressor.h"

#include <QHBoxLayout>

BigProgressor::BigProgressor() : FlatTile(), AnimatorElement()
{
    QHBoxLayout *lay = new QHBoxLayout;
    QVBoxLayout *head = new QVBoxLayout;

    titlebar.setMaximumHeight(30);

    head->addWidget(&titlebar);
    head->addLayout(lay);
    lay->addWidget(&pad);
    lay->addWidget(&message);
    setLayout(head);

    titlebar.setMaximumHeight(20);
    pad.setFixedSize(180, 180);
    message.setFixedSize(200, 180);
    setFixedSize(380, 200);
    setMaximumHeight(200);
}

void BigProgressor::runAnim()
{
    pad.startAnimation();
    QTimer::singleShot(1000, &pad, &CircleProgressAnimatePad::stopAnimation);
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
