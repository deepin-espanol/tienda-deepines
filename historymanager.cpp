#include "historymanager.h"

#include <iostream>
#include "colormodifier.h"

const Color::Modifier FW(Color::FG_WHITE);
const Color::Modifier BB(Color::BG_BLACK);
const Color::Modifier RESET(Color::Code::RESET);
AbstractHistoryHandler::AbstractHistoryHandler() {}
AbstractHistoryHandler::~AbstractHistoryHandler() {}
void AbstractHistoryHandler::load(QString) {}
void AbstractHistoryHandler::unload() {}
QWidget *AbstractHistoryHandler::widget() const {return new QWidget;}

HistoryManager::HistoryManager(QObject *parent) : QObject(parent) {}

HistoryManager::~HistoryManager()
{
    history.~QStringList();
    map.~QMap();
}

void HistoryManager::printHistory()
{
    std::cout << Color::Modifier(Color::Code::BG_CYAN) << Color::Modifier(Color::Code::FG_BLUE)
              << "IDEX:" << index+1
              << ", length: " << history.count()
              << ", current evaluation: " << ((index+1 < history.count()) ? "true" : "false")
              << ", can go forward: " << (canGoForward() ? "true" : "false")
              << RESET << std::endl;
    int i = 0;
    while (i < history.length()) {
        if (i == index) {
            std::cout << FW << BB << history.at(i).toLocal8Bit().data() << RESET << " > ";
        } else {
            std::cout << history.at(i).toLocal8Bit().data() << " > ";
        }
        i++;
    }
    std::cout << std::endl;
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
    return (index > 0);
}

bool HistoryManager::canGoForward()
{
    return (index+1 < history.count());
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
    std::cout << __func__ << ", Status: " << canGoBackward() << std::endl;
    if (canGoBackward()) {
        index--;
        currentHandler->unload();

        AbstractHistoryHandler *h = const_cast<AbstractHistoryHandler *>(parse(history[index]));
        h->load(history[index].split(":").last());

        currentHandler = h;

        Q_EMIT changeTo(h->widget());
        runCheck();
    }
}

void HistoryManager::forward()
{
    std::cout << __func__ << ", Status: " << canGoForward() << std::endl;
    if (canGoForward()) {
        index++;
        std::cout << ", Data: " << history[index].toLocal8Bit().data() << std::endl;
        currentHandler->unload();

        AbstractHistoryHandler *h = const_cast<AbstractHistoryHandler *>(parse(history[index]));
        h->load(history[index].split(":").last());

        currentHandler = h;

        Q_EMIT changeTo(h->widget());
        runCheck();
    }
}

void HistoryManager::cancelLast()
{
     std::cout << __func__ << ", Status: " << canGoBackward() << std::endl;
     if (canGoBackward()) {
         history.removeAt(index);
         index--;
         currentHandler->unload();

         AbstractHistoryHandler *h = const_cast<AbstractHistoryHandler *>(parse(history[index]));
         h->load(history[index].split(":").last());

         currentHandler = h;

         Q_EMIT changeTo(h->widget());
         runCheck();
     }
}

void HistoryManager::goTo(QString data)
{
    if (data != history.at(index)) {

        if (index >= history.count() && data != history[index -1]) {
            std::cout << "Added data to HMGR: " << data.toLocal8Bit().data() << std::endl;
        } else {
            std::cout << "####" << std::endl;
            if (index > 0 && index < history.count()) {
                int i = index+1;
                while (i < history.length()) {
                    std::cout << "Removing of HMGR: " << history[i].toLocal8Bit().data() << std::endl;
                    history.removeAt(index);
                    i++;
                }
            }
        }

        history << data;
        index++;
        currentHandler->unload();

        AbstractHistoryHandler *h = const_cast<AbstractHistoryHandler *>(parse(data));
        h->load(data.split(":").last());

        currentHandler = h;

        Q_EMIT changeTo(h->widget());
        runCheck();
    }
}

void HistoryManager::addHandler(QString ID, const AbstractHistoryHandler *h, bool defHand)
{
    map[ID] = h;
    if (defHand) {
        def = h;
        currentHandler = const_cast<AbstractHistoryHandler *>(h);
        history.clear();
        history << ID + ":";
        index = 0;
        std::cout << "Default handler set." << std::endl;
    }
}

const AbstractHistoryHandler *HistoryManager::parse(QString t)
{
    runCheck();
    printHistory();

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
