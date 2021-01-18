#ifndef SMALLPROGRESSOR_H
#define SMALLPROGRESSOR_H

#include "animatorloader.h"

#include <QWidget>
#include <QLabel>
#include <QProgressBar>

class SmallProgressor : public QWidget, public AnimatorElement
{
    Q_OBJECT
public:
    explicit SmallProgressor();

    operator QWidget &() {return *this;}
    operator QWidget *() {return this;}
    operator AnimatorElement &() {return *this;}
    operator AnimatorElement *() {return this;}

public Q_SLOTS:
    void setPercentage(int p);
    void setMessage(QString msg);

private:
    QLabel message;
    QProgressBar bar;
};

#endif // SMALLPROGRESSOR_H
