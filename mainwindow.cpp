#include "mainwindow.h"
#include "loadingwidget.h"

#include "packagesview.h"
#include "tasksview.h"
#include "commonstorage.h"
#include "packagewidget.h"

#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include "daddonsplittedbar.h"

MainWindow::MainWindow(QApt::Backend *backend) : DAddonSplittedWindow()
{
    LoadingWidget *loading = new LoadingWidget;
    loading->show();

    loading->setCurrentTsk(tr("Creating buttons..."));

    backbutton = new DButtonBoxButton(DStyle::SP_ArrowLeave);
    forwardbutton = new DButtonBoxButton(DStyle::SP_ArrowEnter);
    QList<DButtonBoxButton *> buttonList;

    loading->setCurrentTsk(tr("Creating UI tools"));

    stack = new QStackedWidget(this);
    hmgr = new HistoryManager;
    preload = new PreloadViews;
    titleBarContent = new QFrame;
    bar = new SearchBar(this);
    sideList = new DeviceListView(this);
    mgr = TasksManager::instance();
    pkgs = new PackagesView;
    wi = new PackageWidget;

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
    setRightWidget(stack);

    backbutton->setDisabled(true);
    backbutton->setFixedSize(36, 36);

    forwardbutton->setDisabled(true);
    forwardbutton->setFixedSize(36, 36);

    backbutton->setShortcut(Qt::Key_Left);
    forwardbutton->setShortcut(Qt::Key_Right);

    buttonList << backbutton << forwardbutton;

    buttonBox = new Dtk::Widget::DButtonBox();
    buttonBox->setButtonList(buttonList, false);
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

    loading->setCurrentTsk(tr("Downloading and generating UIs from web"));

    hmgr->addHandler(tr("Music"), preload->load("https://raw.githubusercontent.com/N1coc4colA/test-web/master/music.xwe"));
    hmgr->addHandler(tr("Office"), preload->load("https://raw.githubusercontent.com/N1coc4colA/test-web/master/office.xwe"));
    hmgr->addHandler(tr("Graphism"), preload->load("https://raw.githubusercontent.com/N1coc4colA/test-web/master/graphism.xwe"));
    hmgr->addHandler(tr("Video"), preload->load("https://raw.githubusercontent.com/N1coc4colA/test-web/master/video.xwe"));
    hmgr->addHandler(tr("Games"), preload->load("https://raw.githubusercontent.com/N1coc4colA/test-web/master/games.xwe"));
    hmgr->addHandler(tr("Latest"), preload->load("https://raw.githubusercontent.com/N1coc4colA/test-web/master/latest.xwe"));
    hmgr->addHandler(tr("Transactions"), mgr->view());
    hmgr->addHandler("package-viewer", wi);
    hmgr->addHandler(tr("All packages"), pkgs);
    hmgr->addHandler(tr("Selection"), preload->load("https://raw.githubusercontent.com/N1coc4colA/test-web/master/selection.xwe"), true);

    loading->setCurrentTsk(tr("Updating data"));

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
    int len = hmgr->handlers().length();
    while (i < len) {
        stack->addWidget(hmgr->handlers().at(i)->widget());
        if (i == (len -1)) {
            stack->setCurrentWidget(hmgr->handlers().at(i)->widget());
        }
        i++;
    }

    loading->setCurrentTsk(tr("Loading packages data"));

    pkgs->setPackages(CommonStorage::instance()->bkd->availablePackages());


    loading->setCurrentTsk(tr("Setting UI object's connections"));

    connect(hmgr, &HistoryManager::backwardStatusChanged, backbutton, &DButtonBoxButton::setEnabled);
    connect(hmgr, &HistoryManager::forwardStatusChanged, forwardbutton, &DButtonBoxButton::setDisabled);
    connect(hmgr, &HistoryManager::changeTo, stack, &QStackedWidget::setCurrentWidget);
    connect(forwardbutton, &DButtonBoxButton::clicked, hmgr, &HistoryManager::forward);
    connect(backbutton, &DButtonBoxButton::clicked, hmgr, &HistoryManager::backward);
    connect(sideList, &DeviceListView::selectionChanged, this, [this](QString str) {hmgr->goTo(str+":"); });
    QObject::connect(pkgs, &PackagesView::packageSelected, CommonStorage::instance()->bkd, [this](QString pkg) {
        hmgr->goTo("package-viewer:"+pkg);
    });
    QObject::connect(wi, &PackageWidget::reopen, CommonStorage::instance()->bkd, [this](QString pkg) {
        hmgr->goTo("package-viewer:"+pkg);
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
