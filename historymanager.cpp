#include "historymanager.h"

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
    return (next.length() > 1 );
}

bool HistoryManager::canGoForward()
{
    return (next.length() < old.length());
}

const QWidget *HistoryManager::defaultHandler()
{
    return def;
}

void HistoryManager::backward()
{
    if (current > 1) {
        if (next.length() > 1) {
            current--;
            next.removeAt(current);
            Q_EMIT changeTo(const_cast<QWidget *>(parse(old.at(current))));
        }
    }
}

void HistoryManager::forward()
{
    if (old.length() > 1) {
        if (old.length() > next.length()) {
            current++;
            next.append(old.at(current));
            Q_EMIT changeTo(const_cast<QWidget *>(parse(next.last())));
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
        while (r != old.length()) {
            old.removeAt(r +1);
        }
        current = r -1;
    }
    Q_EMIT changeTo(const_cast<QWidget *>(parse(data)));
}

void HistoryManager::addHandler(QString ID, const QWidget *w, bool defHand)
{
    if (const AbstractHistoryHandler *h = dynamic_cast<const AbstractHistoryHandler *>(w)) {
        map[ID] = h;
        if (defHand) {
            def = w;
        }
        if (defHand) {
            current = 0;
            next.clear();
            old.clear();
            old.append("ID");
            next.append("ID");
        }
    }
}

void HistoryManager::addHandler(QString ID, const AbstractHistoryHandler *h, bool defHand)
{
    map[ID] = h;
    if (defHand) {
        def = h->self();
    }
    if (defHand) {
        current = 0;
        next.clear();
        old.clear();
        old.append("ID");
        next.append("ID");
    }
}

const QWidget *HistoryManager::parse(QString t)
{
    if (oldBk != canGoBackward()) { Q_EMIT backwardStatusChanged(!oldBk); oldBk = !oldBk; }
    if (oldFr != canGoForward()) { Q_EMIT forwardStatusChanged(!oldFr); oldFr = !oldFr; }

    int i = 0;
    while (i<map.keys().length()) {
        if (t.startsWith(map.keys().at(i) + ":")) {
            t.startsWith(map.keys().at(i) + ":");
            return map[map.keys().at(i)]->self();
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
        if (map[map.keys().at(i)]->self() != def) {
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
