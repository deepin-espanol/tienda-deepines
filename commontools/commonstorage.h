#ifndef COMMONSTORAGE_H
#define COMMONSTORAGE_H

#include "packagemodel.h"

#include "commontools/historymanager.h"

class MainWindow;
class CommonStorage;
class WindowManager;
class PackagesView;
class TasksManager;

namespace QApt {
    class Backend;
}

/**
 * @brief (alias wmgr) Accessibility class to edit the window states of the current window.
 */
class WindowManager
{
public:
    void fillTop(bool fill);
    void fillBottom(bool fill);
    void blurTop(bool blur);
    void setBottom(QWidget *b);
};

/**
 * @brief (alias storage) Singleton to store pointers and var to be used over multiple classes
 */
class CommonStorage
{
public:
    explicit CommonStorage();
    inline static CommonStorage *instance() {
        static CommonStorage *storage = new CommonStorage;
        return storage;
    }

    HistoryManager *hmgr;
    QApt::Backend *bkd;
    PackageModel model;
    TasksManager *tskmgr;
    MainWindow *currentWindow;
    WindowManager *wmgr = new WindowManager;
};

static CommonStorage *storage = CommonStorage::instance();
static WindowManager *wmgr = storage->wmgr;

#endif // COMMONSTORAGE_H
