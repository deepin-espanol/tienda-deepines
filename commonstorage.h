#ifndef COMMONSTORAGE_H
#define COMMONSTORAGE_H

#include "historymanager.h"
#include "tasksview.h"
#include "packagesview.h"
#include "mainwindow.h"

#include <QApt/Backend>

class MainWindow;

/**
 * @brief A way to store APT BKD data in the storage
 */
struct APTStorage
{
    int total = 0;
    int garbage = 0;
    int newer = 0;
    int orphan = 0;
    int notDownl = 0;
    int instBrok = 0;
    int nowInstBrok = 0;
    int nowPolBrok = 0;
    int instPolBrok = 0;
    int important = 0;
    int resConf = 0;
    int nowBrok = 0;
    int upgradeable = 0;
    int instPkgs = 0;
    bool alreadyAuth = false;
};

/**
 * @brief (alias wmgr) Accessibility class to edit the window of the current window.
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
 * @brief (alias storage) Singleton to store pointers and var that have over multiple classes
 */
class CommonStorage
{
public:
    explicit CommonStorage();
    inline static CommonStorage *instance() {
        static CommonStorage *storage = new CommonStorage;
        return storage;
    }

    APTStorage aptData;

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
