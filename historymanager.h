#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <QMap>
#include <QWidget>

class AbstractHistoryHandler
{
public:
    AbstractHistoryHandler();
    virtual ~AbstractHistoryHandler();
    //Lets you load with args or perform actions depending of 'em
    virtual void load(QString);
    //Lets you perform operatoins when it leaves the handler (like go forward)
    virtual void unload();
    //A way to access the QWidget*, due to QObject impossible multi-inheritance
    virtual QWidget *widget() const;
};

class HistoryManager : public QObject
{
    Q_OBJECT
public:
    explicit HistoryManager(QObject *parent = nullptr);
    ~HistoryManager();

    bool canGoForward();
    bool canGoBackward();
    const QWidget *defaultHandler();
    //Gives all the used handlers
    QList<const AbstractHistoryHandler *> handlers();
    //If you wanna perform lookups outside the class
    const AbstractHistoryHandler *idToHandler(QString ID);
    QString handlerToID(const AbstractHistoryHandler *);

Q_SIGNALS:
    //TO go to new handlers
    void changeTo(QWidget *);
    //If you wanna enable/disable buttons
    void forwardStatusChanged(bool);
    void backwardStatusChanged(bool);

public Q_SLOTS:
    //For buttons use
    void backward();
    void forward();
    void cancelLast();
    //For in handler requests or other stuff
    void goTo(QString);
    //Add handler and the default one here
    void addHandler(QString ID, const AbstractHistoryHandler *handler, bool defaultHandler = false);

private:
    //To perform lookup for the corresponding handler
    const AbstractHistoryHandler *parse(QString);

    //old is the "source", while next is the "temporary" one.
    //We can "cut" old to correspond to next when we have:
    //Backward > Backward > go to (another)
    QStringList history;
    //The "DB" of handlers with their UIDs
    QMap<QString, const AbstractHistoryHandler *> map;
    //The fallback and root of the history. When set, it removes all the current
    const AbstractHistoryHandler *def = nullptr;
    //Used when we have to call unload() and prepare changes
    AbstractHistoryHandler *currentHandler = nullptr;
    //Default value should be -1, equivalent to source of the history (def. handler)
    int index = -1;
    //Old forward & backward status to don't send many times the same signal.
    bool oldBk = false;
    bool oldFr = false;

    //Used every time we move in the history, checks for the state updates.
    void runCheck();
    void printHistory();
};

#endif // HISTORYMANAGER_H
