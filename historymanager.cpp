#include "historymanager.h"

#include <iostream>

HistoryManager::HistoryManager(QObject *parent) : QObject(parent) {}

HistoryManager::~HistoryManager()
{
    old.~QStringList();
    next.~QStringList();
    map.~QMap();
}

QString HistoryManager::handlerToID(const AbstractHistoryHandler *h)
{
    if (map.values().contains(h)) {
        int i = 0;
        while (i<map.keys().length()) {
            if (map[map.keys().at(i)] == h) {
                return map.keys().at(i);
            }
            i++;
        }
    }
    return "";
}

const AbstractHistoryHandler *HistoryManager::idToHandler(QString ID)
{
    return map[ID];
}

bool HistoryManager::canGoBackward()
{
    return (next.length() > 0);
}

bool HistoryManager::canGoForward()
{
    return (next.length() < old.length());
}

const QWidget *HistoryManager::defaultHandler()
{
    return def->widget();
}

void HistoryManager::runCheck()
{
    if (oldBk != canGoBackward()) { Q_EMIT backwardStatusChanged(!oldBk); oldBk = !oldBk; }
    if (oldFr != canGoForward()) { Q_EMIT forwardStatusChanged(!oldFr); oldFr = !oldFr; }
}

void HistoryManager::backward()
{
    if (current > 1) {
        if (next.length() > 1) {
            current--;
            next.removeAt(current);
            AbstractHistoryHandler *h = const_cast<AbstractHistoryHandler *>(parse(old.at(current)));
            h->load(old.at(current).split(":").last());
            Q_EMIT changeTo(h->widget());
            runCheck();
        }
    }
}

void HistoryManager::forward()
{
    if (next.length() < old.length()) {
        if (old.length() > next.length()) {
            current++;
            next.append(old.at(current));
            AbstractHistoryHandler *h = const_cast<AbstractHistoryHandler *>(parse(old.at(current)));
            h->load(old.at(current).split(":").last());
            Q_EMIT changeTo(h->widget());
            runCheck();
        }
    }
}

void HistoryManager::goTo(QString data)
{
    if (old.length() == next.length()) {
        old.append(data);
        next.append(data);
        current++;
    } else {
        int r = next.length();
        while (r < old.length()) {
            old.removeAt(r);
        }
        current = r -1;
    }
    AbstractHistoryHandler *h = const_cast<AbstractHistoryHandler *>(parse(data));
    h->load(data.split(":").last());
    Q_EMIT changeTo(h->widget());
    runCheck();
}

void HistoryManager::addHandler(QString ID, const AbstractHistoryHandler *h, bool defHand)
{
    map[ID] = h;
    if (defHand) {
        def = h;
    }
    if (defHand) {
        current = -1;
        next.clear();
        old.clear();
        old.append(ID);
        next.append(ID);
    }
}

const AbstractHistoryHandler *HistoryManager::parse(QString t)
{
    runCheck();
    int i = 0;
    while (i<map.keys().length()) {
        if (t.startsWith(map.keys().at(i) + ":")) {
            return map[map.keys().at(i)];
        }
        i++;
    }

    return def;
}

QList<const AbstractHistoryHandler *> HistoryManager::handlers()
{
    int i = 0;
    QList<const AbstractHistoryHandler *> list;
    const AbstractHistoryHandler *defaultOne = nullptr;
    while (i < map.keys().length()) {
        if (map[map.keys().at(i)] != def) {
            const AbstractHistoryHandler *h = map[map.keys().at(i)];
            list << h;
        } else {
            defaultOne = map[map.keys().at(i)];
        }
        i++;
    }
    if (defaultOne != nullptr) {
        list << defaultOne;
    }
    return list;
}
