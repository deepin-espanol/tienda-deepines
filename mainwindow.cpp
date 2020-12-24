#include "mainwindow.h"

#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include "daddonsplittedbar.h"

MainWindow::MainWindow() : DAddonSplittedWindow()
{
    stack = new QStackedWidget(this);
    stack->setAttribute(Qt::WidgetAttribute::WA_TranslucentBackground, false);
    stack->setAutoFillBackground(true);
    setRightWidget(stack);

    backbutton = new DButtonBoxButton(DStyle::SP_ArrowLeave);
    backbutton->setDisabled(true);
    backbutton->setFixedSize(36, 36);

    forwardbutton = new DButtonBoxButton(DStyle::SP_ArrowEnter);
    forwardbutton->setDisabled(true);
    forwardbutton->setFixedSize(36, 36);

    backbutton->setShortcut(Qt::Key_Left);
    forwardbutton->setShortcut(Qt::Key_Right);

    QList<DButtonBoxButton *> buttonList;
    buttonList << backbutton << forwardbutton;

    buttonBox = new Dtk::Widget::DButtonBox();
    buttonBox->setButtonList(buttonList, false);
    buttonBox->setFocusPolicy(Qt::NoFocus);

    bar = new SearchBar(this);
    //bar->setFixedWidth(300);
    bar->setPlaceHolder(tr("Search"));

    titleBarContent = new QFrame;
    QHBoxLayout *lay = new QHBoxLayout;
    QLabel *t = new QLabel("Store Deepines");
    QFont f = t->font();
    f.setBold(true);
    f.setPointSize(14);
    t->setFont(f);
    t->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    t->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

    lay->setContentsMargins(10, 0, 0, 0);
    lay->addWidget(buttonBox, 0, Qt::AlignLeft);
    lay->addWidget(bar);
    //lay->addWidget()

    titleBarContent->setLayout(lay);

    splitedbar()->setCustomTitleAlign(Qt::AlignLeft);
    splitedbar()->setCustomTitleAlign(Qt::AlignVCenter);
    //splitedbar()->setTitle("Store Deepines");
    //splitedbar()->leftLayout()->removeWidget(splitedbar()->leftLayout()->itemAt(1)->widget());
    splitedbar()->leftLayout()->setSpacing(5);
    splitedbar()->leftLayout()->addWidget(t);

    std::cout << splitedbar()->leftLayout()->count() << std::endl;

    splitedbar()->setBlurBackground(true);
    splitedbar()->setBackgroundTransparent(false);
    splitedbar()->setCustomWidget(titleBarContent, true);
    splitedbar()->setCustomTitleAlign(Qt::AlignCenter);

    hmgr = new HistoryManager;

    connect(hmgr, &HistoryManager::backwardStatusChanged, backbutton, &DButtonBoxButton::setDisabled);
    connect(hmgr, &HistoryManager::forwardStatusChanged, forwardbutton, &DButtonBoxButton::setDisabled);

    preload = new PreloadViews;
    //std::cout << test << test->metaObject()->className() << std::endl;
    hmgr->addHandler(tr("Music"), preload->load("https://raw.githubusercontent.com/N1coc4colA/test-web/master/music.xwe"));
    hmgr->addHandler(tr("Office"), preload->load("https://raw.githubusercontent.com/N1coc4colA/test-web/master/desktop.xwe"));
    hmgr->addHandler(tr("Graphism"), preload->load("https://raw.githubusercontent.com/N1coc4colA/test-web/master/graphism.xwe"));
    hmgr->addHandler(tr("Video"), preload->load("https://raw.githubusercontent.com/N1coc4colA/test-web/master/video.xwe"));
    hmgr->addHandler(tr("Games"), preload->load("https://raw.githubusercontent.com/N1coc4colA/test-web/master/games.xwe"));
    hmgr->addHandler(tr("Latest"), preload->load("https://raw.githubusercontent.com/N1coc4colA/test-web/master/latest.xwe"));
    hmgr->addHandler(tr("Selection"), preload->load("https://raw.githubusercontent.com/N1coc4colA/test-web/master/selection.xwe"), true);
    connect(hmgr, &HistoryManager::changeTo, stack, &QStackedWidget::setCurrentWidget);


    sideList = new DeviceListView(this);
    sideList->setAttribute(Qt::WA_TranslucentBackground, true);
    sideList->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    QVBoxLayout *leftLay = new QVBoxLayout;
    leftWidget()->setLayout(leftLay);
    leftLay->setContentsMargins(0, 0, 0, 0);
    leftLay->addItem(new QSpacerItem(0, 50, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed));
    leftLay->addWidget(sideList);

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
    std::cout << (nullptr == nullptr) << len << std::endl;
    while (i < len) {
        stack->addWidget(hmgr->handlers().at(i)->self());
        sideList->setPair(hmgr->handlerToID(hmgr->handlers().at(i)), hmgr->handlers().at(i)->self());
        if (i == (len -1)) {
            stack->setCurrentWidget(hmgr->handlers().at(i)->self());
        }
        i++;
    }
}

MainWindow::~MainWindow()
{
    forwardbutton->~DButtonBoxButton();
    backbutton->~DButtonBoxButton();
    buttonBox->~DButtonBox();
    titleBarContent->layout()->~QLayout();
    titleBarContent->~QFrame();
    stack->~QStackedWidget();
}

void MainWindow::handleViewChange(const QWidget *w)
{
    stack->setCurrentWidget(const_cast<QWidget *>(w));
}
