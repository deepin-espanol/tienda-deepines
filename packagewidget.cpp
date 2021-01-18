#include "packagewidget.h"

#include "datafields.h"
#include "commonstorage.h"
#include "splittedbutton.h"
#include "screenshotwidget.h"
#include "mainwindow.h"

#include "colormodifier.h"

#include "ext/libda-release/daddonsplittedbar.h"
#include <iostream>

#include <QToolButton>
#include <QApplication>
#include <QFormLayout>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QIcon>
#include <QPixmap>
#include <QImage>
#include <QTabBar>
#include <QDesktopServices>
#include <QAction>
#include <QMenu>

static const int MAX_WH_VAL = 16777215;
static const int MAX_LIST_HEIGHT = 280;
static const int MIN_LIST_HEIGHT = 100;
static const int MIN_SSW_HEIGHT = 400;

class PackageWidgetUI
{
public:
    QVBoxLayout *verticalLayout_6;
    QWidget *header_container;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout;
    QLabel *pkgIcon;
    QFormLayout *formLayout;
    QLabel *label_name;
    QLabel *label_version;
    QLabel *label_category;
    QLabel *pkgName;
    QLabel *pkgVersion;
    QLabel *pkgCategory;
    QSpacerItem *horizontalSpacer;
    SplittedButton *pushButton;
    QFrame *line;
    QFrame *description_container;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_description;
    QLabel *pkgDescription;

    DataFields *informations;
    ScreenShotWidget *screenShotWidget;

    QWidget *dependencies_container;
    QVBoxLayout *dependencies_vl;
    QHBoxLayout *dependencies_hl;
    QLabel *dependencies_label;
    QFrame *dependencies_line;
    QListWidget *dependencies_list;

    QWidget *installedFiles_container;
    QVBoxLayout *installedFiles_vl;
    QHBoxLayout *installedFiles_hl;
    QLabel *installedFiles_label;
    QFrame *installedFiles_line;
    QListWidget *installedFiles_list;

    QWidget *requiredBy_container;
    QVBoxLayout *requiredBy_vl;
    QHBoxLayout *requiredBy_hl;
    QLabel *requiredBy_label;
    QFrame *requiredBy_line;
    QListWidget *requiredBy_list;

    QWidget *enhances_container;
    QVBoxLayout *enhances_vl;
    QHBoxLayout *enhances_hl;
    QLabel *enhances_label;
    QFrame *enhances_line;
    QListWidget *enhances_list;

    QWidget *enhancedBy_container;
    QVBoxLayout *enhancedBy_vl;
    QHBoxLayout *enhancedBy_hl;
    QLabel *enhancedBy_label;
    QFrame *enhancedBy_line;
    QListWidget *enhancedBy_list;

    QWidget *recommends_container;
    QVBoxLayout *recommends_vl;
    QHBoxLayout *recommends_hl;
    QLabel *recommends_label;
    QFrame *recommends_line;
    QListWidget *recommends_list;

    QWidget *suggests_container;
    QVBoxLayout *suggests_vl;
    QHBoxLayout *suggests_hl;
    QLabel *suggests_label;
    QFrame *suggests_line;
    QListWidget *suggests_list;

    QWidget *provides_container;
    QVBoxLayout *provides_vl;
    QHBoxLayout *provides_hl;
    QLabel *provides_label;
    QFrame *provides_line;
    QListWidget *provides_list;

    QAction *installIt;
    QAction *removeIt;
    QAction *upgradeIt;
    QAction *purgeIt;
    QAction *reinstallIt;

    QActionGroup *packageActs;
    QMenu *packageActsMenu;

    QSpacerItem *bottomSpacer;

    void setupUi(QWidget *Form)
    {
        verticalLayout_6 = new QVBoxLayout(Form);
        verticalLayout_6->setContentsMargins(8, -1, 8, -1);

        QSpacerItem *top = new QSpacerItem(0, CommonStorage::instance()->currentWindow->splitedbar()->height(),
                                           QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        verticalLayout_6->addItem(top);

        header_container = new QWidget(Form);
        verticalLayout_9 = new QVBoxLayout(header_container);
        verticalLayout_9->setContentsMargins(5, 0, 5, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setContentsMargins(0, 5, 0, 5);
        pkgIcon = new QLabel(header_container);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pkgIcon->sizePolicy().hasHeightForWidth());
        pkgIcon->setSizePolicy(sizePolicy);
        pkgIcon->setMinimumSize(QSize(80, 80));
        pkgIcon->setMaximumSize(QSize(80, 80));
        pkgIcon->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(pkgIcon);

        formLayout = new QFormLayout();
        formLayout->setContentsMargins(10, -1, -1, -1);
        label_name = new QLabel(header_container);
        formLayout->setWidget(0, QFormLayout::LabelRole, label_name);
        label_version = new QLabel(header_container);
        formLayout->setWidget(1, QFormLayout::LabelRole, label_version);
        label_category = new QLabel(header_container);
        formLayout->setWidget(2, QFormLayout::LabelRole, label_category);
        pkgName = new QLabel(header_container);
        formLayout->setWidget(0, QFormLayout::FieldRole, pkgName);
        pkgVersion = new QLabel(header_container);
        formLayout->setWidget(1, QFormLayout::FieldRole, pkgVersion);
        pkgCategory = new QLabel(header_container);
        formLayout->setWidget(2, QFormLayout::FieldRole, pkgCategory);


        horizontalLayout->addLayout(formLayout);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        horizontalLayout->addItem(horizontalSpacer);
        pushButton = new SplittedButton(Form);
        horizontalLayout->addWidget(pushButton);

        verticalLayout_9->addLayout(horizontalLayout);

        line = new QFrame(header_container);
        line->setLineWidth(2);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        verticalLayout_9->addWidget(line);

        description_container = new QFrame(header_container);
        description_container->setMinimumSize(QSize(0, 0));
        description_container->setFrameShape(QFrame::NoFrame);
        description_container->setFrameShadow(QFrame::Raised);
        verticalLayout_8 = new QVBoxLayout(description_container);
        verticalLayout_8->setContentsMargins(5, 8, 5, -1);
        label_description = new QLabel(description_container);
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        label_description->setFont(font);
        label_description->setTextInteractionFlags(Qt::NoTextInteraction);
        verticalLayout_8->addWidget(label_description);

        pkgDescription = new QLabel(description_container);
        verticalLayout_8->addWidget(pkgDescription);
        verticalLayout_9->addWidget(description_container);
        verticalLayout_6->addWidget(header_container);

        informations = new DataFields(Form);
        verticalLayout_6->addWidget(informations);

        screenShotWidget = new ScreenShotWidget(Form);
        screenShotWidget->setMinimumHeight(MIN_SSW_HEIGHT);
        verticalLayout_6->addWidget(screenShotWidget);

        dependencies_container = new QWidget(Form);
        dependencies_vl = new QVBoxLayout(dependencies_container);
        dependencies_vl->setContentsMargins(0, -1, 0, -1);
        dependencies_hl = new QHBoxLayout();
        dependencies_hl->setSizeConstraint(QLayout::SetMinimumSize);
        dependencies_hl->setContentsMargins(-1, 10, -1, -1);
        dependencies_label = new QLabel(dependencies_container);
        QSizePolicy dependencies_sp1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        dependencies_sp1.setHorizontalStretch(0);
        dependencies_sp1.setVerticalStretch(0);
        dependencies_sp1.setHeightForWidth(dependencies_label->sizePolicy().hasHeightForWidth());
        dependencies_label->setSizePolicy(dependencies_sp1);
        dependencies_label->setFont(font);
        dependencies_label->setTextInteractionFlags(Qt::NoTextInteraction);
        dependencies_hl->addWidget(dependencies_label);
        dependencies_line = new QFrame(dependencies_container);
        QSizePolicy dependencies_sp2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        dependencies_sp2.setHorizontalStretch(0);
        dependencies_sp2.setVerticalStretch(0);
        dependencies_sp2.setHeightForWidth(dependencies_line->sizePolicy().hasHeightForWidth());
        dependencies_line->setSizePolicy(dependencies_sp2);
        dependencies_line->setFrameShape(QFrame::HLine);
        dependencies_line->setFrameShadow(QFrame::Sunken);
        dependencies_hl->addWidget(dependencies_line);
        dependencies_vl->addLayout(dependencies_hl);
        dependencies_list = new QListWidget(dependencies_container);
        dependencies_list->setMinimumSize(QSize(0, MIN_LIST_HEIGHT));
        dependencies_list->setMaximumSize(QSize(MAX_WH_VAL, MAX_LIST_HEIGHT));
        dependencies_list->setFrameShape(QFrame::NoFrame);
        dependencies_vl->addWidget(dependencies_list);
        verticalLayout_6->addWidget(dependencies_container);

        installedFiles_container = new QWidget(Form);
        installedFiles_vl = new QVBoxLayout(installedFiles_container);
        installedFiles_vl->setContentsMargins(0, -1, 0, -1);
        installedFiles_hl = new QHBoxLayout();
        installedFiles_hl->setSizeConstraint(QLayout::SetMinimumSize);
        installedFiles_hl->setContentsMargins(-1, 10, -1, -1);
        installedFiles_label = new QLabel(installedFiles_container);
        QSizePolicy installedFiles_sp1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        installedFiles_sp1.setHorizontalStretch(0);
        installedFiles_sp1.setVerticalStretch(0);
        installedFiles_sp1.setHeightForWidth(installedFiles_label->sizePolicy().hasHeightForWidth());
        installedFiles_label->setSizePolicy(installedFiles_sp1);
        installedFiles_label->setFont(font);
        installedFiles_label->setTextInteractionFlags(Qt::NoTextInteraction);
        installedFiles_hl->addWidget(installedFiles_label);
        installedFiles_line = new QFrame(installedFiles_container);
        QSizePolicy installedFiles_sp2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        installedFiles_sp2.setHorizontalStretch(0);
        installedFiles_sp2.setVerticalStretch(0);
        installedFiles_sp2.setHeightForWidth(installedFiles_line->sizePolicy().hasHeightForWidth());
        installedFiles_line->setSizePolicy(installedFiles_sp2);
        installedFiles_line->setFrameShape(QFrame::HLine);
        installedFiles_line->setFrameShadow(QFrame::Sunken);
        installedFiles_hl->addWidget(installedFiles_line);
        installedFiles_vl->addLayout(installedFiles_hl);
        installedFiles_list = new QListWidget(installedFiles_container);
        installedFiles_list->setMinimumHeight(MIN_LIST_HEIGHT);
        installedFiles_list->setMaximumHeight(MAX_LIST_HEIGHT);
        installedFiles_list->setFrameShape(QFrame::NoFrame);
        installedFiles_vl->addWidget(installedFiles_list);
        verticalLayout_6->addWidget(installedFiles_container);

        requiredBy_container = new QWidget(Form);
        requiredBy_vl = new QVBoxLayout(requiredBy_container);
        requiredBy_vl->setContentsMargins(0, -1, 0, -1);
        requiredBy_hl = new QHBoxLayout();
        requiredBy_hl->setSizeConstraint(QLayout::SetMinimumSize);
        requiredBy_hl->setContentsMargins(-1, 10, -1, -1);
        requiredBy_label = new QLabel(requiredBy_container);
        QSizePolicy requiredBy_sp1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        requiredBy_sp1.setHorizontalStretch(0);
        requiredBy_sp1.setVerticalStretch(0);
        requiredBy_sp1.setHeightForWidth(requiredBy_label->sizePolicy().hasHeightForWidth());
        requiredBy_label->setSizePolicy(requiredBy_sp1);
        requiredBy_label->setFont(font);
        requiredBy_label->setTextInteractionFlags(Qt::NoTextInteraction);
        requiredBy_hl->addWidget(requiredBy_label);
        requiredBy_line = new QFrame(requiredBy_container);
        QSizePolicy requiredBy_sp2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        requiredBy_sp2.setHorizontalStretch(0);
        requiredBy_sp2.setVerticalStretch(0);
        requiredBy_sp2.setHeightForWidth(requiredBy_line->sizePolicy().hasHeightForWidth());
        requiredBy_line->setSizePolicy(requiredBy_sp2);
        requiredBy_line->setFrameShape(QFrame::HLine);
        requiredBy_line->setFrameShadow(QFrame::Sunken);
        requiredBy_hl->addWidget(requiredBy_line);
        requiredBy_vl->addLayout(requiredBy_hl);
        requiredBy_list = new QListWidget(requiredBy_container);
        requiredBy_list->setMinimumSize(QSize(0, MIN_LIST_HEIGHT));
        requiredBy_list->setMaximumSize(QSize(MAX_WH_VAL, MAX_LIST_HEIGHT));
        requiredBy_list->setFrameShape(QFrame::NoFrame);
        requiredBy_vl->addWidget(requiredBy_list);
        verticalLayout_6->addWidget(requiredBy_container);

        enhances_container = new QWidget(Form);
        enhances_vl = new QVBoxLayout(enhances_container);
        enhances_vl->setContentsMargins(0, -1, 0, -1);
        enhances_hl = new QHBoxLayout();
        enhances_hl->setSizeConstraint(QLayout::SetMinimumSize);
        enhances_hl->setContentsMargins(-1, 10, -1, -1);
        enhances_label = new QLabel(enhances_container);
        QSizePolicy enhances_sp1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        enhances_sp1.setHorizontalStretch(0);
        enhances_sp1.setVerticalStretch(0);
        enhances_sp1.setHeightForWidth(enhances_label->sizePolicy().hasHeightForWidth());
        enhances_label->setSizePolicy(enhances_sp1);
        enhances_label->setFont(font);
        enhances_label->setTextInteractionFlags(Qt::NoTextInteraction);
        enhances_hl->addWidget(enhances_label);
        enhances_line = new QFrame(enhances_container);
        QSizePolicy enhances_sp2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        enhances_sp2.setHorizontalStretch(0);
        enhances_sp2.setVerticalStretch(0);
        enhances_sp2.setHeightForWidth(enhances_line->sizePolicy().hasHeightForWidth());
        enhances_line->setSizePolicy(enhances_sp2);
        enhances_line->setFrameShape(QFrame::HLine);
        enhances_line->setFrameShadow(QFrame::Sunken);
        enhances_hl->addWidget(enhances_line);
        enhances_vl->addLayout(enhances_hl);
        enhances_list = new QListWidget(enhances_container);
        enhances_list->setMinimumSize(QSize(0, MIN_LIST_HEIGHT));
        enhances_list->setMaximumSize(QSize(MAX_WH_VAL, MAX_LIST_HEIGHT));
        enhances_list->setFrameShape(QFrame::NoFrame);
        enhances_vl->addWidget(enhances_list);
        verticalLayout_6->addWidget(enhances_container);

        enhancedBy_container = new QWidget(Form);
        enhancedBy_vl = new QVBoxLayout(enhancedBy_container);
        enhancedBy_vl->setContentsMargins(0, -1, 0, -1);
        enhancedBy_hl = new QHBoxLayout();
        enhancedBy_hl->setSizeConstraint(QLayout::SetMinimumSize);
        enhancedBy_hl->setContentsMargins(-1, 10, -1, -1);
        enhancedBy_label = new QLabel(enhancedBy_container);
        QSizePolicy enhancedBy_sp1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        enhancedBy_sp1.setHorizontalStretch(0);
        enhancedBy_sp1.setVerticalStretch(0);
        enhancedBy_sp1.setHeightForWidth(enhancedBy_label->sizePolicy().hasHeightForWidth());
        enhancedBy_label->setSizePolicy(enhancedBy_sp1);
        enhancedBy_label->setFont(font);
        enhancedBy_label->setTextInteractionFlags(Qt::NoTextInteraction);
        enhancedBy_hl->addWidget(enhancedBy_label);
        enhancedBy_line = new QFrame(enhancedBy_container);
        QSizePolicy enhancedBy_sp2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        enhancedBy_sp2.setHorizontalStretch(0);
        enhancedBy_sp2.setVerticalStretch(0);
        enhancedBy_sp2.setHeightForWidth(enhancedBy_line->sizePolicy().hasHeightForWidth());
        enhancedBy_line->setSizePolicy(enhancedBy_sp2);
        enhancedBy_line->setFrameShape(QFrame::HLine);
        enhancedBy_line->setFrameShadow(QFrame::Sunken);
        enhancedBy_hl->addWidget(enhancedBy_line);
        enhancedBy_vl->addLayout(enhancedBy_hl);
        enhancedBy_list = new QListWidget(enhancedBy_container);
        enhancedBy_list->setMinimumSize(QSize(0, MIN_LIST_HEIGHT));
        enhancedBy_list->setMaximumSize(QSize(MAX_WH_VAL, MAX_LIST_HEIGHT));
        enhancedBy_list->setFrameShape(QFrame::NoFrame);
        enhancedBy_vl->addWidget(enhancedBy_list);
        verticalLayout_6->addWidget(enhancedBy_container);

        recommends_container = new QWidget(Form);
        recommends_vl = new QVBoxLayout(recommends_container);
        recommends_vl->setContentsMargins(0, -1, 0, -1);
        recommends_hl = new QHBoxLayout();
        recommends_hl->setSizeConstraint(QLayout::SetMinimumSize);
        recommends_hl->setContentsMargins(-1, 10, -1, -1);
        recommends_label = new QLabel(recommends_container);
        QSizePolicy recommends_sp1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        recommends_sp1.setHorizontalStretch(0);
        recommends_sp1.setVerticalStretch(0);
        recommends_sp1.setHeightForWidth(recommends_label->sizePolicy().hasHeightForWidth());
        recommends_label->setSizePolicy(recommends_sp1);
        recommends_label->setFont(font);
        recommends_label->setTextInteractionFlags(Qt::NoTextInteraction);
        recommends_hl->addWidget(recommends_label);
        recommends_line = new QFrame(recommends_container);
        QSizePolicy recommends_sp2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        recommends_sp2.setHorizontalStretch(0);
        recommends_sp2.setVerticalStretch(0);
        recommends_sp2.setHeightForWidth(recommends_line->sizePolicy().hasHeightForWidth());
        recommends_line->setSizePolicy(recommends_sp2);
        recommends_line->setFrameShape(QFrame::HLine);
        recommends_line->setFrameShadow(QFrame::Sunken);
        recommends_hl->addWidget(recommends_line);
        recommends_vl->addLayout(recommends_hl);
        recommends_list = new QListWidget(recommends_container);
        recommends_list->setMinimumSize(QSize(0, MIN_LIST_HEIGHT));
        recommends_list->setMaximumSize(QSize(MAX_WH_VAL, MAX_LIST_HEIGHT));
        recommends_list->setFrameShape(QFrame::NoFrame);
        recommends_vl->addWidget(recommends_list);
        verticalLayout_6->addWidget(recommends_container);

        suggests_container = new QWidget(Form);
        suggests_vl = new QVBoxLayout(suggests_container);
        suggests_vl->setContentsMargins(0, -1, 0, -1);
        suggests_hl = new QHBoxLayout();
        suggests_hl->setSizeConstraint(QLayout::SetMinimumSize);
        suggests_hl->setContentsMargins(-1, 10, -1, -1);
        suggests_label = new QLabel(suggests_container);
        QSizePolicy suggests_sp1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        suggests_sp1.setHorizontalStretch(0);
        suggests_sp1.setVerticalStretch(0);
        suggests_sp1.setHeightForWidth(suggests_label->sizePolicy().hasHeightForWidth());
        suggests_label->setSizePolicy(suggests_sp1);
        suggests_label->setFont(font);
        suggests_label->setTextInteractionFlags(Qt::NoTextInteraction);
        suggests_hl->addWidget(suggests_label);
        suggests_line = new QFrame(suggests_container);
        QSizePolicy suggests_sp2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        suggests_sp2.setHorizontalStretch(0);
        suggests_sp2.setVerticalStretch(0);
        suggests_sp2.setHeightForWidth(suggests_line->sizePolicy().hasHeightForWidth());
        suggests_line->setSizePolicy(suggests_sp2);
        suggests_line->setFrameShape(QFrame::HLine);
        suggests_line->setFrameShadow(QFrame::Sunken);
        suggests_hl->addWidget(suggests_line);
        suggests_vl->addLayout(suggests_hl);
        suggests_list = new QListWidget(suggests_container);
        suggests_list->setMinimumSize(QSize(0, MIN_LIST_HEIGHT));
        suggests_list->setMaximumSize(QSize(MAX_WH_VAL, MAX_LIST_HEIGHT));
        suggests_list->setFrameShape(QFrame::NoFrame);
        suggests_vl->addWidget(suggests_list);
        verticalLayout_6->addWidget(suggests_container);

        provides_container = new QWidget();
        provides_vl = new QVBoxLayout(provides_container);
        provides_vl->setContentsMargins(0, -1, 0, -1);
        provides_hl = new QHBoxLayout();
        provides_hl->setSizeConstraint(QLayout::SetMinimumSize);
        provides_hl->setContentsMargins(-1, 10, -1, -1);
        provides_label = new QLabel(provides_container);
        QSizePolicy provides_sp1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        provides_sp1.setHorizontalStretch(0);
        provides_sp1.setVerticalStretch(0);
        provides_sp1.setHeightForWidth(provides_label->sizePolicy().hasHeightForWidth());
        provides_label->setSizePolicy(provides_sp1);
        provides_label->setFont(font);
        provides_label->setTextInteractionFlags(Qt::NoTextInteraction);
        provides_hl->addWidget(provides_label);
        provides_line = new QFrame(provides_container);
        QSizePolicy provides_sp2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        provides_sp2.setHorizontalStretch(0);
        provides_sp2.setVerticalStretch(0);
        provides_sp2.setHeightForWidth(provides_line->sizePolicy().hasHeightForWidth());
        provides_line->setSizePolicy(provides_sp2);
        provides_line->setFrameShape(QFrame::HLine);
        provides_line->setFrameShadow(QFrame::Sunken);
        provides_hl->addWidget(provides_line);
        provides_vl->addLayout(provides_hl);
        provides_list = new QListWidget(provides_container);
        provides_list->setMinimumSize(QSize(0, 100));
        provides_list->setMaximumSize(QSize(MAX_WH_VAL, 280));
        provides_list->setFrameShape(QFrame::NoFrame);
        provides_vl->addWidget(provides_list);
        verticalLayout_6->addWidget(provides_container);

        recommends_container->setVisible(true);
        suggests_container->setVisible(true);
        provides_container->setVisible(true);
        enhancedBy_container->setVisible(true);
        enhancedBy_container->setVisible(true);
        dependencies_container->setVisible(true);
        installedFiles_container->setVisible(true);
        requiredBy_container->setVisible(true);

        installIt = new QAction(QObject::tr("Install"));
        removeIt = new QAction(QObject::tr("Remove"));
        upgradeIt = new QAction(QObject::tr("Upgrade"));
        purgeIt = new QAction(QObject::tr("Purge"));
        reinstallIt = new QAction(QObject::tr("Reinstall"));

        packageActs = new QActionGroup(Form);
        packageActs->addAction(installIt);
        packageActs->addAction(removeIt);
        packageActs->addAction(upgradeIt);
        packageActs->addAction(purgeIt);
        packageActs->addAction(reinstallIt);
        packageActs->setExclusive(true);

        packageActsMenu = new QMenu;
        packageActsMenu->addActions({upgradeIt, installIt, reinstallIt, removeIt, purgeIt});

        pushButton->setDefaultAction(installIt);
        pushButton->setOptionalMenu(packageActsMenu);

        bottomSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(bottomSpacer);

        retranslateUi(Form);
        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", nullptr));
        pkgIcon->setText(QString());
        label_name->setText(QApplication::translate("Form", "Package Name:", nullptr));
        label_version->setText(QApplication::translate("Form", "Version:", nullptr));
        label_category->setText(QApplication::translate("Form", "Category:", nullptr));
        pkgName->setText(QApplication::translate("Form", "<package_name>", nullptr));
        pkgVersion->setText(QApplication::translate("Form", "<package_version>", nullptr));
        pkgCategory->setText(QApplication::translate("Form", "<package_category>", nullptr));
        label_description->setText(QApplication::translate("Form", "Description", nullptr));
        pkgDescription->setText(QApplication::translate("Form", "Lorem Ipsum Dolor Sit Amen", nullptr));
        dependencies_label->setText(QApplication::translate("Form", "Dependencies", nullptr));
        installedFiles_label->setText(QApplication::translate("Form", "Installed files", nullptr));
        requiredBy_label->setText(QApplication::translate("Form", "Required by", nullptr));
        enhances_label->setText(QApplication::translate("Form", "Enhances", nullptr));
        enhancedBy_label->setText(QApplication::translate("Form", "Enhanced by", nullptr));
        recommends_label->setText(QApplication::translate("Form", "Recommends", nullptr));
        suggests_label->setText(QApplication::translate("Form", "Suggestions", nullptr));
        provides_label->setText(QApplication::translate("Form", "Provides", nullptr));

        informations->setHeaders({
        QApplication::translate("Package Informations", "Maintainer: ", "The maintainer of the package, KDE Dev team, Leo Luccini..."),
        QApplication::translate("Package Informations", "Source: ", "The url of the repo"),
        QApplication::translate("Package Informations", "Web page: ", "The project's (package) page on the web"),
        QApplication::translate("Package Informations", "Package Origin: ", "The origin of the package such as Debian, Deepin...")
        });
    } // retranslateUi

};


PackageWidget::PackageWidget(QWidget *parent) : QScrollArea(parent)
{
    QWidget *widget = new QWidget(this);
    widget->setContentsMargins(0, 0, 0, 5);
    widget->setAutoFillBackground(true);

    ui = new PackageWidgetUI;
    ui->setupUi(widget);
    ui->retranslateUi(this);
    this->setWidget(widget);
    this->setWidgetResizable(true);
    this->setAutoFillBackground(true);

    pkgInfs = new BottomPackageWidgetInformations(CommonStorage::instance()->currentWindow);
    pkgInfs->setVisible(false);
    pkgInfs->setFixedHeight(44);
    pkgInfs->setHeaders({
                            tr("Trusted"),
                            tr("Priority"),
                            tr("MultiArch"),
                            tr("Download size"),
                            tr("Installed size"),
                            tr("Current size"),
                            tr("Component"),
                            tr("Supported until")
    });

    //Setup connections to handle list features
    //Provides can don't give particularly registered package, so we don't use it
    connect(ui->dependencies_list, &QListWidget::doubleClicked, this, [this](QModelIndex index){
        this->handleSelfOpen(index, ui->dependencies_list);
    });
    connect(ui->provides_list, &QListWidget::doubleClicked, this, [this](QModelIndex index){
        this->handleSelfOpen(index, ui->provides_list);
    });
    connect(ui->requiredBy_list, &QListWidget::doubleClicked, this, [this](QModelIndex index){
        this->handleSelfOpen(index, ui->requiredBy_list);
    });
    connect(ui->enhances_list, &QListWidget::doubleClicked, this, [this](QModelIndex index){
        this->handleSelfOpen(index, ui->enhances_list);
    });
    connect(ui->enhancedBy_list, &QListWidget::doubleClicked, this, [this](QModelIndex index){
        this->handleSelfOpen(index, ui->enhancedBy_list);
    });
    connect(ui->suggests_list, &QListWidget::doubleClicked, this, [this](QModelIndex index){
        this->handleSelfOpen(index, ui->suggests_list);
    });
    connect(ui->installedFiles_list, &QListWidget::doubleClicked, this, [this](QModelIndex index){
        this->handleSelfOpen(index, ui->installedFiles_list);
    });

    //Setup connections to handle package's actions
    connect(ui->installIt, &QAction::triggered, this, [this] () {
        CommonStorage::instance()->bkd->markPackages({}, QApt::Package::State::ToInstall);
        CommonStorage::instance()->tskmgr->addTransaction(
            CommonStorage::instance()->bkd->commitChanges(),
            tr("Installing ") + oldPkg->name()
        );
    });
    connect(ui->removeIt, &QAction::triggered, this, [this] () {
        CommonStorage::instance()->bkd->markPackages({}, QApt::Package::State::ToRemove);
        CommonStorage::instance()->tskmgr->addTransaction(
            CommonStorage::instance()->bkd->commitChanges(),
            tr("Removing ") + oldPkg->name()
        );
    });
    connect(ui->purgeIt, &QAction::triggered, this, [this] () {
        CommonStorage::instance()->bkd->markPackages({}, QApt::Package::State::ToPurge);
        CommonStorage::instance()->tskmgr->addTransaction(
            CommonStorage::instance()->bkd->commitChanges(),
            tr("Purging ") + oldPkg->name()
        );
    });
    connect(ui->upgradeIt, &QAction::triggered, this, [this] () {
        CommonStorage::instance()->bkd->markPackages({}, QApt::Package::State::ToUpgrade);
        CommonStorage::instance()->tskmgr->addTransaction(
            CommonStorage::instance()->bkd->commitChanges(),
            tr("Upgrading ") + oldPkg->name()
        );
    });
    connect(ui->reinstallIt, &QAction::triggered, this, [this] () {
        CommonStorage::instance()->bkd->markPackages({}, QApt::Package::State::ToReInstall);
        CommonStorage::instance()->tskmgr->addTransaction(
            CommonStorage::instance()->bkd->commitChanges(),
            tr("Reinstalling ") + oldPkg->name()
        );
    });
}

void PackageWidget::handleSelfOpen(QModelIndex index, QListWidget *w)
{
    if (w != ui->installedFiles_list) {
            //Parse to get the right pkg
            QRegularExpression rx(": ([a-zA-Z0-9!@#$%^\\-\\.&_+]+)");

            rx.setPatternOptions(QRegularExpression::NoPatternOption);
            QRegularExpressionMatchIterator iterator = rx.globalMatch(w->item(index.row())->data(0).toString(), 0, QRegularExpression::NormalMatch, QRegularExpression::NoMatchOption);

            //iterator.next(); //To remove the first (': <pkg>")
            Q_EMIT reopen(iterator.next().captured(1));

    } else {
        //Open as file
        QUrl url = QUrl::fromLocalFile(w->item(index.row())->data(0).toString());
        QUrl out(url.path().remove(url.fileName()));
        QDesktopServices::openUrl(out);
    }
}

PackageWidget::~PackageWidget()
{
    m_layout->~QHBoxLayout();
    delete ui;
    this->QScrollArea::~QScrollArea();
}

bool PackageWidget::setPackage(QApt::Package *pkg)
{
    if (pkg != nullptr) {
        if (pkg != oldPkg) {
            oldPkg = pkg;
            reloadUI();
        }
        return true;
    } else {
        CommonStorage::instance()->hmgr->backward();
    }
    return false;
}

void PackageWidget::load(QString str)
{
    if (setPackage(CommonStorage::instance()->bkd->package(str))) {
        CommonStorage::instance()->currentWindow->setFillTop(true);
        CommonStorage::instance()->currentWindow->setFillBottom(false);
        CommonStorage::instance()->currentWindow->splitedbar()->setBlurBackground(true);
        CommonStorage::instance()->currentWindow->setBottomWidget(pkgInfs);
        pkgInfs->setVisible(true);
    } else {
        std::cout << Color::Modifier(Color::Code::BG_RED) << Color::Modifier(Color::Code::FG_WHITE)
                  << "Error while trying to get \"" << str.toLocal8Bit().data()
                  << "\"" << Color::Modifier(Color::Code::RESET)
                  << std::endl;
        CommonStorage::instance()->hmgr->cancelLast();
    }
}

void PackageWidget::unload()
{
}

void PackageWidget::reloadUI()
{
    //Clear our fields, and make checkups to don't make any useless calculations!
    ui->pkgVersion->setText(oldPkg->version());

    ui->informations->setData({
        oldPkg->maintainer(),
        oldPkg->homepage(),
        oldPkg->site(),
        oldPkg->origin()
    });

    pkgInfs->setData({
        (oldPkg->isTrusted() ? tr("Yes") : tr("No")),
        oldPkg->priority(),
        ((QApt::MultiArchSame == oldPkg->multiArchType()) ? tr("Same") :
            ((QApt::MultiArchAllowed == oldPkg->multiArchType()) ? tr("Allowed") :
                ((QApt::MultiArchForeign == oldPkg->multiArchType()) ? tr("Foreign") : "")
            )
        ),
        QString::number(oldPkg->downloadSize()),
        QString::number(oldPkg->availableInstalledSize()),
        QString::number(oldPkg->currentInstalledSize()),
        oldPkg->component(),
        oldPkg->supportedUntil().toString()
    });

    QUrl SSUrl(oldPkg->screenshotUrl(QApt::ScreenshotType::Screenshot));
    if (SSUrl.isEmpty() == false && SSUrl != QUrl("") && SSUrl != QUrl(" ") && (QString(SSUrl.toString(QUrl::None)).contains("http:/") == true || QString(SSUrl.toString(QUrl::None)).contains("https:/") == true)) {
        qDebug() << SSUrl;
        ui->screenShotWidget->load(&SSUrl);
     } else {
        ui->screenShotWidget->setVisible(false);
    }

    ui->pkgName->setText(oldPkg->name());
    ui->pkgCategory->setText(oldPkg->section());
    ui->pkgVersion->setText(oldPkg->version());
    ui->pkgDescription->setText(oldPkg->shortDescription()); // [TODO] We will add an expand option and then show the longDescription()

    if (QIcon::hasThemeIcon(oldPkg->name())) {
        ui->pkgIcon->setPixmap(QIcon::fromTheme(oldPkg->name()).pixmap(ui->pkgIcon->size()));
    } else {
        ui->pkgIcon->setPixmap(QIcon::fromTheme("synaptic").pixmap(ui->pkgIcon->size()));
    }

    // Deps
    if (!oldPkg->dependencyList(true).isEmpty()) {
            ui->dependencies_container->setVisible(true);
        ui->dependencies_list->clear();
        //Parse to clear text issues
        QStringList list = oldPkg->dependencyList(true);
        QStringList out;
        int i = 0;
        while (i < list.length()) { //Remove the last as it's the pkg itself
            QString data = list.at(i);
            out.append(data.remove("<b>").remove("</b>").remove("<i>").remove("</i>"));
            i++;
        }
        ui->dependencies_list->addItems(out);
    } else {
            ui->dependencies_container->setVisible(false);
    }

    // Installed files
    if (!oldPkg->installedFilesList().isEmpty()) {
            ui->installedFiles_container->setVisible(true);
        ui->installedFiles_list->clear();
        ui->installedFiles_list->addItems(oldPkg->installedFilesList());
    } else {
            ui->installedFiles_container->setVisible(false);
    }

    // Required pkgs
    if (!oldPkg->requiredByList().isEmpty()) {
            ui->requiredBy_container->setVisible(true);
        ui->requiredBy_list->clear();
        ui->requiredBy_list->addItems(oldPkg->requiredByList());
    } else {
            ui->requiredBy_container->setVisible(false);
    }

    // Provides
    if (!oldPkg->providesList().isEmpty()) {
            ui->provides_container->setVisible(true);
        ui->provides_list->clear();
        ui->provides_list->addItems(oldPkg->providesList());
    } else {
            ui->provides_container->setVisible(false);
    }

    // Enhances
    if (!oldPkg->enhancesList().isEmpty()) {
            ui->enhances_container->setVisible(true);
        ui->enhances_list->clear();
        ui->enhances_list->addItems(oldPkg->enhancesList());
    } else {
            ui->enhances_container->setVisible(false);
    }

    // Enhanced by
    if (!oldPkg->enhancedByList().isEmpty()) {
            ui->enhancedBy_container->setVisible(true);
        ui->enhancedBy_list->clear();
        ui->enhancedBy_list->addItems(oldPkg->enhancedByList());
    } else {
            ui->enhancedBy_container->setVisible(false);
    }

    // Recommends
    if (!oldPkg->recommendsList().isEmpty()) {
            ui->recommends_container->setVisible(true);
        ui->recommends_list->clear();
        ui->recommends_list->addItems(oldPkg->recommendsList());
    } else {
            ui->recommends_container->setVisible(false);
    }

    // Suggests
    if (!oldPkg->suggestsList().isEmpty()) {
            ui->suggests_container->setVisible(true);
        ui->suggests_list->clear();
        ui->suggests_list->addItems(oldPkg->suggestsList());
    } else {
            ui->suggests_container->setVisible(false);
    }


    QAction *lastUsed = nullptr;
    bool shouldDisable = false;

    bool e = (QApt::Package::State::ToInstall & oldPkg->state());
    ui->installIt->setChecked(e);
    if (e) {
        shouldDisable = e;
        lastUsed = ui->installIt;
    }
    e = (QApt::Package::State::ToRemove & oldPkg->state());
    ui->removeIt->setChecked(e);
    if (e) {
        shouldDisable = e;
        lastUsed = ui->removeIt;
    }
    e = (QApt::Package::State::ToPurge & oldPkg->state());
    ui->purgeIt->setChecked(e);
    if (e) {
        shouldDisable = e;
        lastUsed = ui->purgeIt;
    }
    e = (QApt::Package::State::ToReInstall & oldPkg->state());
    ui->reinstallIt->setChecked(e);
    if (e) {
        shouldDisable = e;
        lastUsed = ui->reinstallIt;
    }
    e = (QApt::Package::State::ToUpgrade & oldPkg->state());
    ui->upgradeIt->setChecked(e);
    if (e) {
        shouldDisable = e;
        lastUsed = ui->purgeIt;
    }

    ui->packageActs->setDisabled(shouldDisable);
    ui->pushButton->setDisabled(shouldDisable);

    if (!shouldDisable) {
        if (!oldPkg->isInstalled()) {
            lastUsed = ui->installIt;
        } else {
            if (QApt::Package::State::Upgradeable & oldPkg->state()) {
                lastUsed = ui->upgradeIt;
            } else {
                lastUsed = ui->removeIt;
            }
        }

        if (ui->packageActs->checkedAction() != nullptr) {
            ui->packageActs->checkedAction()->setChecked(false);
        }

        ui->upgradeIt->setEnabled((QApt::Package::State::Upgradeable & oldPkg->state()));
        ui->installIt->setDisabled((oldPkg->isInstalled() || (QApt::Package::State::Upgradeable & oldPkg->state())));
        ui->removeIt->setEnabled(oldPkg->isInstalled());
        ui->reinstallIt->setEnabled(oldPkg->isInstalled());
        //The purge action should always be visible as the package can leave data after uninstall. Just keep it.
    }

    ui->pushButton->setDefaultAction(lastUsed);

    /* [TODO] Make special SVG icons for informations about the PKG
     *
     * [SPECIAL] Add another that isn't in the flags list: is trusted? <------ a ✓ icon
        /// The package has been held from being upgraded
        Held                = 1 << 7,       <------ I didn't understand the exact meaning of that, we leave it like that so, not handled yet.
        /// The package is currently upgradeable
        Upgradeable         = 1 << 9,       <------ upgrade (up arrow) icon
        /// The package is currently broken
        NowBroken           = 1 << 10,      <------ a broken circle or link icon
        /// The package's install is broken
        InstallBroken       = 1 << 11,      <------ icon with a "⬡" in another "⬡", the middle transparent
        /// This package is a dependency of another package that is not installed
        Orphaned            = 1 << 12,//    <------ a transparent dot in another, like DDE's style for check boxes
        /// The package has been manually prevented from upgrade
        Pinned              = 1 << 13,//    <------ banned upgrade (up arrow) icon
        /// The package is new in the archives
        New                 = 1 << 14,//    <------ something like a green star with a "!" or just "new" in white with red BG
        /// The package still has residual config. (Was not purged)
        ResidualConfig      = 1 << 15,      <------ little dots like garbage
        /// The package is no longer downloadable
        NotDownloadable     = 1 << 16,      <------ banned download (down arrow) icon
        /// The package is essential for a base installation
        IsImportant         = 1 << 18,      <------ a warning icon transparent triangle and the "!" and wha's out of the triangle in orange-yellow
        /// The package was automatically installed as a dependency
        IsAuto              = 1 << 20,      <------ a simple connection, a dot with an arrow like "⚫--> ⚫" to say that's related to another pkg
        /// The package's policy is broken
        NowPolicyBroken     = 1 << 22,      <------ a banned "P"
        /// The package's install policy is broken
        InstallPolicyBroken = 1 << 23,      <------ the "⬡" in the "⬡" or a "◊" cut by a X and in front of that a "P"
        */
}
