#ifndef ABSTRACTHISTORYHANDLER_H
#define ABSTRACTHISTORYHANDLER_H

#include <QWidget>

class AbstractHistoryHandler
{
public:
    AbstractHistoryHandler();
    virtual ~AbstractHistoryHandler();
    virtual void load(QString);
    virtual QWidget *widget() const;
};

#endif // ABSTRACTHISTORYHANDLER_H
