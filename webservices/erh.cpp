#include "erh.h"

#include "commontools/commonstorage.h"

ERH::ERH(QObject *parent) : QObject(parent) {}

template <typename Func> void ERH::bridge(const typename QtPrivate::FunctionPointer<Func>::Object *src, Func sig)
{
    connect(src, sig, this, &ERH::generatePkgRequest);
}

void ERH::generatePkgRequest(QString n)
{
    storage->hmgr->goTo("package-viewer:" + n);
}
