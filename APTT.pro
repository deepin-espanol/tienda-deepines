#-------------------------------------------------
#
# Project created by QtCreator 2020-11-26T22:21:42
#
#-------------------------------------------------

QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = APTT
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17 link_pkgconfig debug
PKGCONFIG = dtkwidget dtkcore libqapt

SOURCES += \
        main.cpp \
    tasksview.cpp \
    packagesview.cpp \
    filterwidget.cpp \
    sortmodel.cpp \
    packagewidget.cpp \
    form.cpp \
    datafields.cpp \
    appsectionview.cpp \
    commonstorage.cpp \
    proxydatamodel.cpp \
    filteroptionswidget.cpp \
    historymanager.cpp \
    mainwindow.cpp \
    searchbar.cpp \
    preloadviews.cpp \
    ext/undtk/DeviceListView.cpp \
    dxwengine.cpp \
    loadingwidget.cpp \
    splittedbutton.cpp \
    screenshotwidget.cpp \
    bottompackagewidgetinformations.cpp \
    statisticsview.cpp \
    nodeepineswarn.cpp \
    statistics/circleprogressanimatepad.cpp \
    statistics/smallprogressor.cpp \
    statistics/bigprogressor.cpp \
    statistics/animatorloader.cpp \
    Qt/flowlayout.cpp

unix:!macx: LIBS += -lKF5CoreAddons -lKF5KIOCore -ldebconf-kde

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    tasksview.h \
    packagesview.h \
    filterwidget.h \
    sortmodel.h \
    packagewidget.h \
    form.h \
    datafields.h \
    appsectionview.h \
    commonstorage.h \
    proxydatamodel.h \
    filteroptionswidget.h \
    historymanager.h \
    mainwindow.h \
    searchbar.h \
    preloadviews.h \
    ext/undtk/DeviceListView.h \
    dxwengine.h \
    loadingwidget.h \
    splittedbutton.h \
    ui_screenshotwidget.h \
    screenshotwidget.h \
    bottompackagewidgetinformations.h \
    colormodifier.h \
    statisticsview.h \
    nodeepineswarn.h \
    statistics/circleprogressanimatepad.h \
    statistics/smallprogressor.h \
    statistics/bigprogressor.h \
    statistics/animatorloader.h \
    Qt/flowlayout.h

RESOURCES += \
    main.qrc

FORMS += \
    form.ui

unix:!macx: LIBS += -llibDA

INCLUDEPATH += $$PWD/ext/libda-release
