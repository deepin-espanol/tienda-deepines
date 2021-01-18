#ifndef COMMONSTORAGE_H
#define COMMONSTORAGE_H

#include "historymanager.h"
#include "tasksview.h"
#include "packagesview.h"
#include <qapt/backend.h>

class MainWindow;

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
};

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
};

#endif // COMMONSTORAGE_H
