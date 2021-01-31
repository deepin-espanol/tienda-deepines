#include "smallprogressor.h"

#include <QHBoxLayout>

SmallProgressor::SmallProgressor() : FlatTile()
{
    QVBoxLayout *lay = new QVBoxLayout;
    lay->setMargin(0);
    message.setContentsMargins(3, 3, 3, 3);
    message.setWordWrap(true);
    lay->addWidget(&message);
    lay->addWidget(&bar);
    setLayout(lay);

    message.setFixedSize(200, 190);
    bar.setFixedSize(200, 10);
    setFixedSize(200, 200);
}

void SmallProgressor::setMessage(QString msg)
{
    message.setText(msg);
}

void SmallProgressor::setPercentage(int p)
{
    bar.setValue(p);
}
