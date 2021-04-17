#-------------------------------------------------
#
# Project created by QtCreator 2020-11-26T22:21:42
#
#-------------------------------------------------

QT       += core gui network xml dbus

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

CONFIG += c++17 link_pkgconfig
PKGCONFIG = dtkwidget dtkcore libqapt

SOURCES += \
        main.cpp \
    ext/undtk/DeviceListView.cpp \
    tasksview.cpp \
    splittedbutton.cpp \
    sortmodel.cpp \
    searchbar.cpp \
    proxydatamodel.cpp \
    preloadviews.cpp \
    packagesview.cpp \
    mainwindow.cpp \
    appsectionview.cpp \
    filteroptionswidget.cpp \
    filterwidget.cpp \
    loadingwidget.cpp \
    packagewidgets/bottompackagewidgetinformations.cpp \
    packagewidgets/datafields.cpp \
    packagewidgets/packagewidget.cpp \
    packagewidgets/screenshotwidget.cpp \
    webservices/dxwengine.cpp \
    commontools/commonstorage.cpp \
    commontools/historymanager.cpp \
    commontools/utils.cpp \
    packagewidgets/headerbar.cpp \
    webservices/iconlist.cpp \
    webservices/bannerelement.cpp \
    webservices/horizontallineelement.cpp \
    webservices/headerlabel.cpp \
    webservices/pathmaker.cpp \
    webservices/coverlist.cpp \
    webservices/dynamicressourceloader.cpp \
    commontools/imagery.cpp \
    webservices/spacers.cpp \
    webservices/iconelement.cpp \
    webservices/labeladdon.cpp \
    webservices/erh.cpp \
    webservices/fillerelement.cpp \
    packagemodel.cpp

unix:!macx: LIBS += -lKF5CoreAddons -lKF5KIOCore -ldebconf-kde


HEADERS += \
    ext/undtk/DeviceListView.h \
    ui_screenshotwidget.h \
    tasksview.h \
    splittedbutton.h \
    sortmodel.h \
    searchbar.h \
    proxydatamodel.h \
    preloadviews.h \
    packagesview.h \
    mainwindow.h \
    appsectionview.h \
    filteroptionswidget.h \
    filterwidget.h \
    loadingwidget.h \
    packagewidgets/bottompackagewidgetinformations.h \
    packagewidgets/datafields.h \
    packagewidgets/packagewidget.h \
    packagewidgets/screenshotwidget.h \
    webservices/dxwengine.h \
    commontools/commonstorage.h \
    commontools/historymanager.h \
    commontools/utils.h \
    packagewidgets/headerbar.h \
    webservices/iconlist.h \
    webservices/bannerelement.h \
    webservices/horizontallineelement.h \
    webservices/headerlabel.h \
    webservices/pathmaker.h \
    webservices/coverlist.h \
    webservices/dynamicressourceloader.h \
    commontools/imagery.h \
    webservices/spacers.h \
    webservices/iconelement.h \
    webservices/labeladdon.h \
    webservices/erh.h \
    webservices/fillerelement.h \
    packagemodel.h

RESOURCES += \
    main.qrc

FORMS += \
    form.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx: LIBS += -llibDA

INCLUDEPATH += $$PWD/ext/libda-release
