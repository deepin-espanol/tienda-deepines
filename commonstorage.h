#ifndef COMMONSTORAGE_H
#define COMMONSTORAGE_H

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

    QApt::Backend bkd;
    PackageModel model;
};

#endif // COMMONSTORAGE_H
