#ifndef COMMONSTORAGE_H
#define COMMONSTORAGE_H

#include "historymanager.h"
#include "tasksview.h"
#include "packagesview.h"
#include <qapt/backend.h>

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
};

#endif // COMMONSTORAGE_H
