#include "mainwindow.h"
#include "loadingwidget.h"

#include "packagesview.h"
#include "tasksview.h"
#include "commonstorage.h"
#include "packagewidget.h"
#include "statisticsview.h"
#include "dragview.h"

#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include "daddonsplittedbar.h"

MainWindow::MainWindow(QWidget *p) : DAddonSplittedWindow(p)
{
    LoadingWidget *loading = new LoadingWidget;
    loading->show();

    storage->currentWindow = this;
    loading->setCurrentTsk(tr("Creating buttons"));

    backbutton = new DButtonBoxButton(DStyle::SP_ArrowLeave);
    forwardbutton = new DButtonBoxButton(DStyle::SP_ArrowEnter);

    loading->setCurrentTsk(tr("Creating views"));

    stack = new QStackedWidget(this);
    storage->hmgr = new HistoryManager;
    preload = new PreloadViews;
    titleBarContent = new QFrame;
    bar = new SearchBar(this);
    sideList = new DeviceListView(this);
    storage->tskmgr = TasksManager::instance();
    pkgs = new PackagesView;
    wi = new PackageWidget;
    stats = new StatisticsView;
    ofv = new OpenFileView;

    loading->setCurrentTsk(tr("Creating layouts"));

    QHBoxLayout *lay = new QHBoxLayout;
    QVBoxLayout *leftLay = new QVBoxLayout;
    QLabel *t = new QLabel("Tienda Deepines");

    loading->setCurrentTsk(tr("Settuping titlebar"));

    splitedbar()->setBlurBackground(true);
    splitedbar()->setBackgroundTransparent(false);
    splitedbar()->setCustomWidget(titleBarContent, true);
    splitedbar()->setCustomTitleAlign(Qt::AlignCenter);

    loading->setCurrentTsk(tr("Settuping UI components"));

    sideList->setAttribute(Qt::WA_TranslucentBackground, true);
    sideList->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

    stack->setAttribute(Qt::WidgetAttribute::WA_TranslucentBackground, false);
    stack->setAutoFillBackground(true);
    stack->setLineWidth(0);
    setRightWidget(stack);

    backbutton->setDisabled(true);
    backbutton->setFixedSize(36, 36);

    forwardbutton->setDisabled(true);
    forwardbutton->setFixedSize(36, 36);

    backbutton->setShortcut(Qt::Key_Left);
    forwardbutton->setShortcut(Qt::Key_Right);

    buttonBox = new Dtk::Widget::DButtonBox();
    buttonBox->setButtonList({backbutton, forwardbutton}, false);
    buttonBox->setFocusPolicy(Qt::NoFocus);

    bar->setPlaceHolder(tr("Search"));

    QFont f = t->font();
    f.setBold(true);
    f.setPointSize(14);
    t->setFont(f);
    t->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    t->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

    loading->setCurrentTsk(tr("Settuping layouts"));

    lay->setContentsMargins(10, 0, 0, 0);
    lay->addWidget(buttonBox, 0, Qt::AlignLeft);
    lay->addWidget(bar);

    titleBarContent->setLayout(lay);

    splitedbar()->setCustomTitleAlign(Qt::AlignLeft);
    splitedbar()->setCustomTitleAlign(Qt::AlignVCenter);
    splitedbar()->leftLayout()->setSpacing(5);
    splitedbar()->leftLayout()->addWidget(t);
    leftWidget()->setLayout(leftLay);
    leftLay->setContentsMargins(0, 0, 0, 0);
    leftLay->addItem(new QSpacerItem(0, 50, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed));
    leftLay->addWidget(sideList);

    loading->setCurrentTsk(tr("Loading packages' data"));
    pkgs->setPackages(storage->bkd->availablePackages());

    loading->setCurrentTsk(tr("Downloading and generating UIs from web"));

    storage->hmgr->addHandler(tr("Music"), preload->load("https://raw.githubusercontent.com/N1coc4colA/test-web/master/music.xwe"));
    storage->hmgr->addHandler(tr("Office"), preload->load("https://raw.githubusercontent.com/N1coc4colA/test-web/master/office.xwe"));
    storage->hmgr->addHandler(tr("Graphism"), preload->load("https://raw.githubusercontent.com/N1coc4colA/test-web/master/graphism.xwe"));
    storage->hmgr->addHandler(tr("Video"), preload->load("https://raw.githubusercontent.com/N1coc4colA/test-web/master/video.xwe"));
    storage->hmgr->addHandler(tr("Games"), preload->load("https://raw.githubusercontent.com/N1coc4colA/test-web/master/games.xwe"));
    storage->hmgr->addHandler(tr("Latest"), preload->load("https://raw.githubusercontent.com/N1coc4colA/test-web/master/latest.xwe"));
    storage->hmgr->addHandler(tr("Transactions"), storage->tskmgr->view());
    storage->hmgr->addHandler("package-viewer", wi);
    storage->hmgr->addHandler(tr("All packages"), pkgs);
    storage->hmgr->addHandler(tr("Statistics"), stats);
    storage->hmgr->addHandler(tr("From local"), ofv);
    storage->hmgr->addHandler(tr("Selection"), preload->load("https://raw.githubusercontent.com/N1coc4colA/test-web/master/selection.xwe"), true);

    loading->setCurrentTsk(tr("Updating UI..."));

    sideList->setItemSpacing(3);
    sideList->addItem(tr("Selection"), ":/deepines.svg");
    sideList->addItem(tr("Office"), ":/deepines.svg");
    sideList->addItem(tr("Music"), ":/deepines.svg");
    sideList->addItem(tr("Graphism"), ":/deepines.svg");
    sideList->addItem(tr("Video"), ":/deepines.svg");
    sideList->addItem(tr("Games"), ":/deepines.svg");
    sideList->addItem(tr("Latest"), ":/deepines.svg");
    sideList->addItem("§separator", "");
    sideList->addItem(tr("All packages"), ":/deepines.svg");
    sideList->addItem(tr("Transactions"), ":/deepines.svg");
    sideList->addItem(tr("Statistics"), ":/deepines.svg");
    sideList->addItem(tr("From local"), ":/deepines.svg");

    int i = 0;
    int len = storage->hmgr->handlers().length();
    while (i < len) {
        stack->addWidget(storage->hmgr->handlers().at(i)->widget());
        if (i == (len -1)) {
            stack->setCurrentWidget(storage->hmgr->handlers().at(i)->widget());
        }
        i++;
    }

    loading->setCurrentTsk(tr("Setting UI object's connections"));

    connect(storage->hmgr, &HistoryManager::backwardStatusChanged, backbutton, &DButtonBoxButton::setEnabled);
    connect(storage->hmgr, &HistoryManager::forwardStatusChanged, forwardbutton, &DButtonBoxButton::setEnabled);
    connect(storage->hmgr, &HistoryManager::changeTo, stack, &QStackedWidget::setCurrentWidget);
    connect(forwardbutton, &DButtonBoxButton::clicked, storage->hmgr, &HistoryManager::forward);
    connect(backbutton, &DButtonBoxButton::clicked, storage->hmgr, &HistoryManager::backward);
    connect(sideList, &DeviceListView::selectionChanged, this, [](QString str) {storage->hmgr->goTo(str+":"); });
    QObject::connect(pkgs, &PackagesView::packageSelected, storage->bkd, [](QString pkg) {
        storage->hmgr->goTo("package-viewer:"+pkg);
    });
    QObject::connect(wi, &PackageWidget::reopen, storage->bkd, [](QString pkg) {
        storage->hmgr->goTo("package-viewer:"+pkg);
    });

    loading->~LoadingWidget();
}

MainWindow::~MainWindow()
{
    forwardbutton->~DButtonBoxButton();
    backbutton->~DButtonBoxButton();
    buttonBox->~DButtonBox();
    titleBarContent->layout()->~QLayout();
    titleBarContent->~QFrame();
    stack->~QStackedWidget();
    bar->~SearchBar();
    preload->~PreloadViews();
    sideList->~DeviceListView();
}

void MainWindow::handleViewChange(const QWidget *w)
{
    stack->setCurrentWidget(const_cast<QWidget *>(w));
}
