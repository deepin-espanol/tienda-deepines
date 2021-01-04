#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApt/Backend>

#include "searchbar.h"
#include "historymanager.h"
#include "preloadviews.h"
#include "ext/undtk/DeviceListView.h"

#include "daddonsplittedwindow.h"
#include <dbuttonbox.h>
#include <QStackedWidget>

class TasksManager;
class PackagesView;
class PackageWidget;

DWIDGET_USE_NAMESPACE
LDA_USE_NAMESPACE

class MainWindow : public DAddonSplittedWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QApt::Backend *backend);
    ~MainWindow();

public Q_SLOTS:
    void handleViewChange(const QWidget *w);

private:
    QFrame *titleBarContent = nullptr;
    DButtonBox *buttonBox = nullptr;
    DButtonBoxButton *backbutton = nullptr;
    DButtonBoxButton *forwardbutton = nullptr;
    QStackedWidget *stack = nullptr;
    SearchBar *bar = nullptr;
    PreloadViews *preload = nullptr;
    DeviceListView *sideList = nullptr;
    PackagesView *pkgs = nullptr;
    PackageWidget *wi = nullptr;
};

#endif // MAINWINDOW_H
