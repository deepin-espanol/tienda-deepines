#include "commonstorage.h"

#include "mainwindow.h"
#include "ext/libda-release/daddonsplittedbar.h"

CommonStorage::CommonStorage() {}

void WindowManager::setBottom(QWidget *b) {storage->currentWindow->setBottomWidget(b);}
void WindowManager::fillTop(bool fill) {storage->currentWindow->setFillTop(fill);}
void WindowManager::fillBottom(bool fill) {storage->currentWindow->setFillBottom(fill);}
void WindowManager::blurTop(bool blur) {storage->currentWindow->splitedbar()->setBlurBackground(blur);}
