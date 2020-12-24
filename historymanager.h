#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include "abstracthistoryhandler.h"

#include <QMap>
#include <QObject>

class HistoryManager : public QObject
{
    Q_OBJECT
public:
    explicit HistoryManager(QObject *parent = nullptr);
    ~HistoryManager();

    bool canGoForward();
    bool canGoBackward();
    const QWidget *defaultHandler();
    QList<const AbstractHistoryHandler *> handlers();
    const AbstractHistoryHandler *idToHandler(QString ID);
    QString handlerToID(const AbstractHistoryHandler *);

Q_SIGNALS:
    void changeTo(QWidget *);
    void forwardStatusChanged(bool);
    void backwardStatusChanged(bool);

public Q_SLOTS:
    void backward();
    void forward();
    void goTo(QString);
    void addHandler(QString ID, const AbstractHistoryHandler *handler, bool defaultHandler = false);

private:
    const QWidget *parse(QString);
    QStringList old;
    QStringList next;
    QMap<QString, const AbstractHistoryHandler *> map;
    const QWidget *def = nullptr;
    int current = -1;
    bool oldBk = false;
    bool oldFr = false;
};

#endif // HISTORYMANAGER_H
