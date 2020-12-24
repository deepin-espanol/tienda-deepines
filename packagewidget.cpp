#include "packagewidget.h"

#include "datafields.h"

#include <iostream>

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QIcon>
#include <QPixmap>
#include <QImage>
#include <QTabBar>
#include <QDesktopServices>

class PackageWidgetUI
{
public:
    QVBoxLayout *verticalLayout_6;
    QFrame *frame_6;
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
    QPushButton *pushButton;
    QFrame *line;
    QVBoxLayout *verticalLayout_7;
    QFrame *frame_5;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_description;
    QLabel *pkgDescription;
    DataFields *informations;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_2;

    QWidget *widget;

    QFrame *frame_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_dependencies;
    QFrame *line_4;
    QListWidget *listDeps;

    QFrame *frame_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_neededby;
    QFrame *line_2;
    QListWidget *listNeedBy;

    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_instfiles;
    QFrame *line_3;
    QListWidget *listFiles;

    QListWidget *listEnhances;
    QFrame *frame_Enhances;
    QVBoxLayout *verticalLayout_Enhances;
    QHBoxLayout *horizontalLayout_Enhances;
    QLabel *label_Enhances;
    QFrame *line_Enhances;

    QListWidget *listProvides;
    QFrame *frame_Provides;
    QVBoxLayout *verticalLayout_Provides;
    QHBoxLayout *horizontalLayout_Provides;
    QLabel *label_Provides;
    QFrame *line_Provides;

    QListWidget *listRecommends;
    QFrame *frame_Recommends;
    QVBoxLayout *verticalLayout_Recommends;
    QHBoxLayout *horizontalLayout_Recommends;
    QLabel *label_Recommends;
    QFrame *line_Recommends;

    QListWidget *listSuggests;
    QFrame *frame_Suggests;
    QVBoxLayout *verticalLayout_Suggests;
    QHBoxLayout *horizontalLayout_Suggests;
    QLabel *label_Suggests;
    QFrame *line_Suggests;

    QListWidget *listEnhancedBy;
    QFrame *frame_EnhancedBy;
    QVBoxLayout *verticalLayout_EnhancedBy;
    QHBoxLayout *horizontalLayout_EnhancedBy;
    QLabel *label_EnhancedBy;
    QFrame *line_EnhancedBy;

    void setupUi(QWidget *Form)
    {
        verticalLayout_6 = new QVBoxLayout(Form);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        frame_6 = new QFrame(Form);
        frame_6->setObjectName(QStringLiteral("frame_6"));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        verticalLayout_9 = new QVBoxLayout(frame_6);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(0, -1, 0, -1);
        verticalLayout_9->setMargin(5);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pkgIcon = new QLabel(frame_6);
        pkgIcon->setObjectName(QStringLiteral("pkgIcon"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pkgIcon->sizePolicy().hasHeightForWidth());
        pkgIcon->setSizePolicy(sizePolicy);
        pkgIcon->setMinimumSize(QSize(80, 80));
        pkgIcon->setMaximumSize(QSize(80, 80));

        horizontalLayout->addWidget(pkgIcon);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(10, -1, -1, -1);
        label_name = new QLabel(frame_6);
        label_name->setObjectName(QStringLiteral("label_name"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_name);

        label_version = new QLabel(frame_6);
        label_version->setObjectName(QStringLiteral("label_version"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_version);

        label_category = new QLabel(frame_6);
        label_category->setObjectName(QStringLiteral("label_category"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_category);

        pkgName = new QLabel(frame_6);
        pkgName->setObjectName(QStringLiteral("pkgName"));

        formLayout->setWidget(0, QFormLayout::FieldRole, pkgName);

        pkgVersion = new QLabel(frame_6);
        pkgVersion->setObjectName(QStringLiteral("pkgVersion"));

        formLayout->setWidget(1, QFormLayout::FieldRole, pkgVersion);

        pkgCategory = new QLabel(frame_6);
        pkgCategory->setObjectName(QStringLiteral("pkgCategory"));

        formLayout->setWidget(2, QFormLayout::FieldRole, pkgCategory);


        horizontalLayout->addLayout(formLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(frame_6);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout_9->addLayout(horizontalLayout);

        line = new QFrame(frame_6);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_9->addWidget(line);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(-1, 0, -1, -1);
        frame_5 = new QFrame(frame_6);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        frame_5->setMinimumSize(QSize(0, 0));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        verticalLayout_8 = new QVBoxLayout(frame_5);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        label_description = new QLabel(frame_5);
        label_description->setObjectName(QStringLiteral("label_description"));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        label_description->setFont(font);
        label_description->setTextInteractionFlags(Qt::NoTextInteraction);

        verticalLayout_8->addWidget(label_description);

        pkgDescription = new QLabel(frame_5);
        pkgDescription->setObjectName(QStringLiteral("pkgDescription"));

        verticalLayout_8->addWidget(pkgDescription);


        verticalLayout_7->addWidget(frame_5);


        verticalLayout_9->addLayout(verticalLayout_7);



        informations = new DataFields(Form);
        informations->setObjectName(QStringLiteral("informations"));


        widget = new QWidget(Form);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QStringLiteral("background-color: rgb(0, 123, 255);"));

        frame_2 = new QFrame(Form);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame_2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, -1, 0, -1);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 10, -1, -1);
        label_dependencies = new QLabel(frame_2);
        label_dependencies->setObjectName(QStringLiteral("label_dependencies"));
        label_dependencies->setFont(font);
        label_dependencies->setTextInteractionFlags(Qt::NoTextInteraction);

        horizontalLayout_4->addWidget(label_dependencies);

        line_4 = new QFrame(frame_2);
        line_4->setObjectName(QStringLiteral("line_4"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(line_4->sizePolicy().hasHeightForWidth());
        line_4->setSizePolicy(sizePolicy1);
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        horizontalLayout_4->addWidget(line_4);


        verticalLayout_3->addLayout(horizontalLayout_4);

        listDeps = new QListWidget(frame_2);
        listDeps->setObjectName(QStringLiteral("listDeps"));

        verticalLayout_3->addWidget(listDeps);

        frame_3 = new QFrame(Form);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(frame_3);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, -1, 0, -1);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 0, -1, -1);
        label_neededby = new QLabel(frame_3);
        label_neededby->setObjectName(QStringLiteral("label_neededby"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_neededby->sizePolicy().hasHeightForWidth());
        label_neededby->setSizePolicy(sizePolicy2);
        label_neededby->setFont(font);
        label_neededby->setTextInteractionFlags(Qt::NoTextInteraction);

        horizontalLayout_3->addWidget(label_neededby);

        line_2 = new QFrame(frame_3);
        line_2->setObjectName(QStringLiteral("line_2"));
        sizePolicy1.setHeightForWidth(line_2->sizePolicy().hasHeightForWidth());
        line_2->setSizePolicy(sizePolicy1);
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line_2);


        verticalLayout_4->addLayout(horizontalLayout_3);

        listNeedBy = new QListWidget(frame_3);
        listNeedBy->setObjectName(QStringLiteral("listNeedBy"));

        verticalLayout_4->addWidget(listNeedBy);

        frame = new QFrame(Form);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, -1, 0, -1);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, 10, -1, -1);
        label_instfiles = new QLabel(frame);
        label_instfiles->setObjectName(QStringLiteral("label_instfiles"));
        label_instfiles->setFont(font);
        label_instfiles->setTextInteractionFlags(Qt::NoTextInteraction);

        horizontalLayout_5->addWidget(label_instfiles);

        line_3 = new QFrame(frame);
        line_3->setObjectName(QStringLiteral("line_3"));
        sizePolicy1.setHeightForWidth(line_3->sizePolicy().hasHeightForWidth());
        line_3->setSizePolicy(sizePolicy1);
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout_5->addWidget(line_3);


        verticalLayout_2->addLayout(horizontalLayout_5);

        listFiles = new QListWidget(frame);
        listFiles->setObjectName(QStringLiteral("listFiles"));

        verticalLayout_2->addWidget(listFiles);

        frame_Enhances = new QFrame(Form);
        frame_Enhances->setObjectName(QStringLiteral("frame_Enhances"));
        frame_Enhances->setFrameShape(QFrame::StyledPanel);
        frame_Enhances->setFrameShadow(QFrame::Raised);
        verticalLayout_Enhances = new QVBoxLayout(frame_Enhances);
        verticalLayout_Enhances->setObjectName(QStringLiteral("verticalLayout_Enhances"));
        verticalLayout_Enhances->setContentsMargins(0, -1, 0, -1);
        horizontalLayout_Enhances = new QHBoxLayout();
        horizontalLayout_Enhances->setObjectName(QStringLiteral("horizontalLayout_Enhances"));
        horizontalLayout_Enhances->setContentsMargins(-1, 0, -1, -1);
        label_Enhances = new QLabel(frame_Enhances);
        label_Enhances->setObjectName(QStringLiteral("label_Enhances"));
        QSizePolicy sizePolicyEnhances(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicyEnhances.setHorizontalStretch(0);
        sizePolicyEnhances.setVerticalStretch(0);
        sizePolicyEnhances.setHeightForWidth(label_Enhances->sizePolicy().hasHeightForWidth());
        label_Enhances->setSizePolicy(sizePolicyEnhances);
        label_Enhances->setFont(font);
        label_Enhances->setTextInteractionFlags(Qt::NoTextInteraction);

        horizontalLayout_Enhances->addWidget(label_Enhances);

        line_Enhances = new QFrame(frame_Enhances);
        line_Enhances->setObjectName(QStringLiteral("line_Enhances"));
        sizePolicyEnhances.setHeightForWidth(line_Enhances->sizePolicy().hasHeightForWidth());
        line_Enhances->setSizePolicy(sizePolicyEnhances);
        line_Enhances->setFrameShape(QFrame::HLine);
        line_Enhances->setFrameShadow(QFrame::Sunken);

        horizontalLayout_Enhances->addWidget(line_Enhances);


        verticalLayout_Enhances->addLayout(horizontalLayout_Enhances);

        listEnhances = new QListWidget(frame_Enhances);
        listEnhances->setObjectName(QStringLiteral("listEnhances"));

        verticalLayout_Enhances->addWidget(listEnhances);



        frame_Provides = new QFrame(Form);
        frame_Provides->setObjectName(QStringLiteral("frame_Provides"));
        frame_Provides->setFrameShape(QFrame::StyledPanel);
        frame_Provides->setFrameShadow(QFrame::Raised);
        verticalLayout_Provides = new QVBoxLayout(frame_Provides);
        verticalLayout_Provides->setObjectName(QStringLiteral("verticalLayout_Provides"));
        verticalLayout_Provides->setContentsMargins(0, -1, 0, -1);
        horizontalLayout_Provides = new QHBoxLayout();
        horizontalLayout_Provides->setObjectName(QStringLiteral("horizontalLayout_Provides"));
        horizontalLayout_Provides->setContentsMargins(-1, 0, -1, -1);
        label_Provides = new QLabel(frame_Provides);
        label_Provides->setObjectName(QStringLiteral("label_Provides"));
        QSizePolicy sizePolicyProvides(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicyProvides.setHorizontalStretch(0);
        sizePolicyProvides.setVerticalStretch(0);
        sizePolicyProvides.setHeightForWidth(label_Provides->sizePolicy().hasHeightForWidth());
        label_Provides->setSizePolicy(sizePolicyProvides);
        label_Provides->setFont(font);
        label_Provides->setTextInteractionFlags(Qt::NoTextInteraction);

        horizontalLayout_Provides->addWidget(label_Provides);

        line_Provides = new QFrame(frame_Provides);
        line_Provides->setObjectName(QStringLiteral("line_Provides"));
        sizePolicyProvides.setHeightForWidth(line_Provides->sizePolicy().hasHeightForWidth());
        line_Provides->setSizePolicy(sizePolicyProvides);
        line_Provides->setFrameShape(QFrame::HLine);
        line_Provides->setFrameShadow(QFrame::Sunken);

        horizontalLayout_Provides->addWidget(line_Provides);


        verticalLayout_Provides->addLayout(horizontalLayout_Provides);

        listProvides = new QListWidget(frame_Provides);
        listProvides->setObjectName(QStringLiteral("listProvides"));

        verticalLayout_Provides->addWidget(listProvides);



        frame_Recommends = new QFrame(Form);
        frame_Recommends->setObjectName(QStringLiteral("frame_Recommends"));
        frame_Recommends->setFrameShape(QFrame::StyledPanel);
        frame_Recommends->setFrameShadow(QFrame::Raised);
        verticalLayout_Recommends = new QVBoxLayout(frame_Recommends);
        verticalLayout_Recommends->setObjectName(QStringLiteral("verticalLayout_Recommends"));
        verticalLayout_Recommends->setContentsMargins(0, -1, 0, -1);
        horizontalLayout_Recommends = new QHBoxLayout();
        horizontalLayout_Recommends->setObjectName(QStringLiteral("horizontalLayout_Recommends"));
        horizontalLayout_Recommends->setContentsMargins(-1, 0, -1, -1);
        label_Recommends = new QLabel(frame_Recommends);
        label_Recommends->setObjectName(QStringLiteral("label_Recommends"));
        QSizePolicy sizePolicyRecommends(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicyRecommends.setHorizontalStretch(0);
        sizePolicyRecommends.setVerticalStretch(0);
        sizePolicyRecommends.setHeightForWidth(label_Recommends->sizePolicy().hasHeightForWidth());
        label_Recommends->setSizePolicy(sizePolicyRecommends);
        label_Recommends->setFont(font);
        label_Recommends->setTextInteractionFlags(Qt::NoTextInteraction);

        horizontalLayout_Recommends->addWidget(label_Recommends);

        line_Recommends = new QFrame(frame_Recommends);
        line_Recommends->setObjectName(QStringLiteral("line_Recommends"));
        sizePolicyRecommends.setHeightForWidth(line_Recommends->sizePolicy().hasHeightForWidth());
        line_Recommends->setSizePolicy(sizePolicyRecommends);
        line_Recommends->setFrameShape(QFrame::HLine);
        line_Recommends->setFrameShadow(QFrame::Sunken);

        horizontalLayout_Recommends->addWidget(line_Recommends);


        verticalLayout_Recommends->addLayout(horizontalLayout_Recommends);

        listRecommends = new QListWidget(frame_Recommends);
        listRecommends->setObjectName(QStringLiteral("listRecommends"));

        verticalLayout_Recommends->addWidget(listRecommends);

        frame_Suggests = new QFrame(Form);
        frame_Suggests->setObjectName(QStringLiteral("frame_Suggests"));
        frame_Suggests->setFrameShape(QFrame::StyledPanel);
        frame_Suggests->setFrameShadow(QFrame::Raised);
        verticalLayout_Suggests = new QVBoxLayout(frame_Suggests);
        verticalLayout_Suggests->setObjectName(QStringLiteral("verticalLayout_Suggests"));
        verticalLayout_Suggests->setContentsMargins(0, -1, 0, -1);
        horizontalLayout_Suggests = new QHBoxLayout();
        horizontalLayout_Suggests->setObjectName(QStringLiteral("horizontalLayout_Suggests"));
        horizontalLayout_Suggests->setContentsMargins(-1, 0, -1, -1);
        label_Suggests = new QLabel(frame_Suggests);
        label_Suggests->setObjectName(QStringLiteral("label_Suggests"));
        QSizePolicy sizePolicySuggests(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicySuggests.setHorizontalStretch(0);
        sizePolicySuggests.setVerticalStretch(0);
        sizePolicySuggests.setHeightForWidth(label_Suggests->sizePolicy().hasHeightForWidth());
        label_Suggests->setSizePolicy(sizePolicySuggests);
        label_Suggests->setFont(font);
        label_Suggests->setTextInteractionFlags(Qt::NoTextInteraction);

        horizontalLayout_Suggests->addWidget(label_Suggests);

        line_Suggests = new QFrame(frame_Suggests);
        line_Suggests->setObjectName(QStringLiteral("line_Suggests"));
        sizePolicySuggests.setHeightForWidth(line_Suggests->sizePolicy().hasHeightForWidth());
        line_Suggests->setSizePolicy(sizePolicySuggests);
        line_Suggests->setFrameShape(QFrame::HLine);
        line_Suggests->setFrameShadow(QFrame::Sunken);

        horizontalLayout_Suggests->addWidget(line_Suggests);


        verticalLayout_Suggests->addLayout(horizontalLayout_Suggests);

        listSuggests = new QListWidget(frame_Suggests);
        listSuggests->setObjectName(QStringLiteral("listSuggests"));

        verticalLayout_Suggests->addWidget(listSuggests);


        frame_EnhancedBy = new QFrame(Form);
        frame_EnhancedBy->setObjectName(QStringLiteral("frame_EnhancedBy"));
        frame_EnhancedBy->setFrameShape(QFrame::StyledPanel);
        frame_EnhancedBy->setFrameShadow(QFrame::Raised);
        verticalLayout_EnhancedBy = new QVBoxLayout(frame_EnhancedBy);
        verticalLayout_EnhancedBy->setObjectName(QStringLiteral("verticalLayout_EnhancedBy"));
        verticalLayout_EnhancedBy->setContentsMargins(0, -1, 0, -1);
        horizontalLayout_EnhancedBy = new QHBoxLayout();
        horizontalLayout_EnhancedBy->setObjectName(QStringLiteral("horizontalLayout_EnhancedBy"));
        horizontalLayout_EnhancedBy->setContentsMargins(-1, 0, -1, -1);
        label_EnhancedBy = new QLabel(frame_EnhancedBy);
        label_EnhancedBy->setObjectName(QStringLiteral("label_EnhancedBy"));
        QSizePolicy sizePolicyEnhancedBy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicyEnhancedBy.setHorizontalStretch(0);
        sizePolicyEnhancedBy.setVerticalStretch(0);
        sizePolicyEnhancedBy.setHeightForWidth(label_EnhancedBy->sizePolicy().hasHeightForWidth());
        label_EnhancedBy->setSizePolicy(sizePolicyEnhancedBy);
        label_EnhancedBy->setFont(font);
        label_EnhancedBy->setTextInteractionFlags(Qt::NoTextInteraction);

        horizontalLayout_EnhancedBy->addWidget(label_EnhancedBy);

        line_EnhancedBy = new QFrame(frame_EnhancedBy);
        line_EnhancedBy->setObjectName(QStringLiteral("line_EnhancedBy"));
        sizePolicyEnhancedBy.setHeightForWidth(line_EnhancedBy->sizePolicy().hasHeightForWidth());
        line_EnhancedBy->setSizePolicy(sizePolicy1);
        line_EnhancedBy->setFrameShape(QFrame::HLine);
        line_EnhancedBy->setFrameShadow(QFrame::Sunken);

        horizontalLayout_EnhancedBy->addWidget(line_EnhancedBy);


        verticalLayout_EnhancedBy->addLayout(horizontalLayout_EnhancedBy);

        listEnhancedBy = new QListWidget(frame_EnhancedBy);
        listEnhancedBy->setObjectName(QStringLiteral("listEnhancedBy"));

        verticalLayout_EnhancedBy->addWidget(listEnhancedBy);



        listDeps->setMaximumHeight(250);
        listFiles->setMaximumHeight(250);
        listNeedBy->setMaximumHeight(250);
        listEnhances->setMaximumHeight(250);
        listProvides->setMaximumHeight(250);
        listSuggests->setMaximumHeight(250);
        listEnhancedBy->setMaximumHeight(250);
        listRecommends->setMaximumHeight(250);

        QLayout::SizeConstraint cont = QLayout::SizeConstraint::SetMinimumSize;

        verticalLayout_Enhances->setSizeConstraint(cont);
        verticalLayout_Recommends->setSizeConstraint(cont);
        verticalLayout_Suggests->setSizeConstraint(cont);
        verticalLayout_Provides->setSizeConstraint(cont);
        verticalLayout_EnhancedBy->setSizeConstraint(cont);
        verticalLayout_3->setSizeConstraint(cont);
        verticalLayout_4->setSizeConstraint(cont);
        verticalLayout_2->setSizeConstraint(cont);

        horizontalLayout_Enhances->setSizeConstraint(cont);
        horizontalLayout_Recommends->setSizeConstraint(cont);
        horizontalLayout_Suggests->setSizeConstraint(cont);
        horizontalLayout_Provides->setSizeConstraint(cont);
        horizontalLayout_EnhancedBy->setSizeConstraint(cont);
        horizontalLayout_3->setSizeConstraint(cont);
        horizontalLayout_4->setSizeConstraint(cont);
        horizontalLayout_5->setSizeConstraint(cont);

        verticalLayout_7->setSizeConstraint(cont);

        frame_Provides->setMaximumHeight(280);
        frame->setMaximumHeight(280); //Files list
        frame_2->setMaximumHeight(280); //Pkg deps
        frame_3->setMaximumHeight(280); //Pkgs that needs it
        frame_Enhances->setMaximumHeight(280);
        frame_EnhancedBy->setMaximumHeight(280);
        frame_Recommends->setMaximumHeight(280);
        frame_Suggests->setMaximumHeight(280);


        verticalLayout_6->addWidget(frame_6); //Pkg description (top)
        verticalLayout_6->addWidget(informations); //Pkg origin (data, 2nd)
        verticalLayout_6->addWidget(widget); //Current replacement for the pkg in action pictures

        verticalLayout_6->addWidget(frame_Provides);
        verticalLayout_6->addWidget(frame); //Files list
        verticalLayout_6->addWidget(frame_2); //Pkg deps
        verticalLayout_6->addWidget(frame_3); //Pkgs that needs it
        verticalLayout_6->addWidget(frame_Enhances);
        verticalLayout_6->addWidget(frame_EnhancedBy);
        verticalLayout_6->addWidget(frame_Recommends);
        verticalLayout_6->addWidget(frame_Suggests);

        frame->setLineWidth(0);
        frame_2->setLineWidth(0);
        frame_3->setLineWidth(0);
        frame_Enhances->setLineWidth(0);
        frame_Provides->setLineWidth(0);
        frame_EnhancedBy->setLineWidth(0);
        frame_Recommends->setLineWidth(0);
        frame_Suggests->setLineWidth(0);
        frame_5->setLineWidth(0);
        frame_6->setFrameShape(QFrame::Shape::StyledPanel);

        listDeps->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        listDeps->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        listFiles->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        listFiles->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        listEnhances->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        listEnhances->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        listEnhancedBy->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        listEnhancedBy->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        listRecommends->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        listRecommends->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        listSuggests->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        listSuggests->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        listProvides->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        listProvides->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        listNeedBy->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        listNeedBy->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

        verticalLayout_6->addItem(new QSpacerItem(0,0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Ignored));
        verticalLayout_6->addItem(new QSpacerItem(0,0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding));
        Form->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));


        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi()
    {
        pkgIcon->setText(QString());
        label_name->setText(QApplication::translate("Package Informations", "Package Name:", nullptr));
        label_version->setText(QApplication::translate("Package Informations", "Version:", nullptr));
        label_category->setText(QApplication::translate("Package Informations", "Category:", "Package's category, such as Game, Utility..."));
        pushButton->setText(QApplication::translate("Package Informations", "Install"));
        label_description->setText(QApplication::translate("Package Informations", "Description", "Description of the package (short or long one)"));

        informations->setHeaders({
        QApplication::translate("Package Informations", "Maintainer: ", "The maintainer of the package, KDE Dev team, Leo Luccini..."),
        QApplication::translate("Package Informations", "Source: ", "The url of the repo"),
        QApplication::translate("Package Informations", "Web page: ", "The project's (package) page on the web"),
        QApplication::translate("Package Informations", "Package Origin: ", "The origin of the package such as Debian, Deepin...")
        });

        label_dependencies->setText(QApplication::translate("Package Informations", "Dependencies", "The packages needed by this package"));
        label_neededby->setText(QApplication::translate("Package Informations", "Needed by", "Packages that requires this package"));
        label_instfiles->setText(QApplication::translate("Package Informations", "Installed files", nullptr));
        label_Enhances->setText(QApplication::translate("Package Informations", "Enhances", "Which package(s) it enhances"));
        label_Provides->setText(QApplication::translate("Package Informations", "Provides", "A package can 'provide' some others like 'dde' that gives all that is needed for DDE."));
        label_Suggests->setText(QApplication::translate("Package Informations", "Suggestions", "Packages that can be installed, a suggestion so"));
        label_EnhancedBy->setText(QApplication::translate("Package Informations", "Enhanced by", "Packages that enhance this one"));
        label_Recommends->setText(QApplication::translate("Package Informations", "Recommends", "Recommendations for this package"));
    }

};

PackageWidget::PackageWidget(QWidget *parent) : QScrollArea(parent)
{
    QWidget *widget = new QWidget(this);
    widget->setContentsMargins(0, 0, 0, 5);
    widget->setAutoFillBackground(true);
    ui = new PackageWidgetUI;
    ui->setupUi(widget);
    ui->retranslateUi();
    this->setWidget(widget);
    this->setWidgetResizable(true);
    this->setAutoFillBackground(true);

    //Setup connections to handle list features
    //Provides can don't give particularly registered package, so we don't use it
    connect(ui->listDeps, &QListWidget::doubleClicked, this, [this](QModelIndex index){
        this->handleSelfOpen(index, ui->listDeps);
    });
    connect(ui->listProvides, &QListWidget::doubleClicked, this, [this](QModelIndex index){
        this->handleSelfOpen(index, ui->listProvides);
    });
    connect(ui->listNeedBy, &QListWidget::doubleClicked, this, [this](QModelIndex index){
        this->handleSelfOpen(index, ui->listNeedBy);
    });
    connect(ui->listEnhances, &QListWidget::doubleClicked, this, [this](QModelIndex index){
        this->handleSelfOpen(index, ui->listEnhances);
    });
    connect(ui->listEnhancedBy, &QListWidget::doubleClicked, this, [this](QModelIndex index){
        this->handleSelfOpen(index, ui->listEnhancedBy);
    });
    connect(ui->listSuggests, &QListWidget::doubleClicked, this, [this](QModelIndex index){
        this->handleSelfOpen(index, ui->listSuggests);
    });
    connect(ui->listFiles, &QListWidget::doubleClicked, this, [this](QModelIndex index){
        this->handleSelfOpen(index, ui->listFiles);
    });
}

void PackageWidget::handleSelfOpen(QModelIndex index, QListWidget *w)
{
    if (w != ui->listFiles) {
        if (w != ui->listDeps) {
            Q_EMIT reopen(w->item(index.row())->data(0).toString());
        } else {

            //Parse to get the right pkg
            QRegularExpression rx(": ([a-zA-Z0-9!@#$%^&_+]+)");

            rx.setPatternOptions(QRegularExpression::NoPatternOption);
            QRegularExpressionMatchIterator iterator = rx.globalMatch(w->item(index.row())->data(0).toString(), 0, QRegularExpression::NormalMatch, QRegularExpression::NoMatchOption);

            //iterator.next(); //To remove the first (': <pkg>")
            Q_EMIT reopen(iterator.next().captured(1));
        }
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

void PackageWidget::setPackage(QApt::Package *pkg)
{
    if (pkg != nullptr && pkg != oldPkg) {
            oldPkg = pkg;
        std::cout << "Package installed: " << oldPkg->isInstalled() << std::endl;
        reloadUI();
    }
}

void PackageWidget::reloadUI()
{
    //Clear our fields, and make checkups to don't make any useless alocations!

    ui->pkgVersion->setText(oldPkg->version());

    ui->informations->setData({
        oldPkg->maintainer(),
        oldPkg->homepage(),
        oldPkg->site(),
        oldPkg->origin()
    });

    ui->pkgName->setText(oldPkg->name());
    ui->pkgCategory->setText(oldPkg->section());
    ui->pkgVersion->setText(oldPkg->version());
    ui->pkgDescription->setText(oldPkg->shortDescription());

    if (QIcon::hasThemeIcon(oldPkg->name())) {
        ui->pkgIcon->setPixmap(QIcon::fromTheme(oldPkg->name()).pixmap(ui->pkgIcon->size()));
    } else {
        ui->pkgIcon->setPixmap(QIcon::fromTheme("synaptic").pixmap(ui->pkgIcon->size()));
    }

    // Deps
    if (!oldPkg->dependencyList(true).isEmpty()) {
        if (!ui->frame_2->isVisible()) {
            ui->frame_2->setVisible(true);
        }
        ui->listDeps->clear();
        //Parse to clear text issues
        QStringList list = oldPkg->dependencyList(true);
        QStringList out;
        int i = 0;
        while (i < list.length()) { //Remove the last as it's the pkg itself
            QString data = list.at(i);
            out.append(data.remove("<b>").remove("</b>").remove("<i>").remove("</i>"));
            i++;
        }
        ui->listNeedBy->addItems(out);
        ui->listDeps->addItems(out);
    } else {
        if (ui->frame_2->isVisible()) {
            ui->frame_2->setVisible(false);
        }
    }

    // Installed files
    if (!oldPkg->installedFilesList().isEmpty()) {
        if (!ui->frame->isVisible()) {
            ui->frame->setVisible(true);
        }
        ui->listFiles->clear();
        ui->listFiles->addItems(oldPkg->installedFilesList());
    } else {
        if (ui->frame->isVisible()) {
            ui->frame->setVisible(false);
        }
    }

    // Required pkgs
    if (!oldPkg->requiredByList().isEmpty()) {
        if (!ui->label_neededby->isVisible()) {
            ui->label_neededby->setVisible(true);
        }
        ui->listNeedBy->clear();
        ui->listNeedBy->addItems(oldPkg->requiredByList());
    } else {
        if (ui->label_neededby->isVisible()) {
            ui->listNeedBy->setVisible(false);
        }
    }

    // Provides
    if (!oldPkg->providesList().isEmpty()) {
        if (!ui->frame_Provides->isVisible()) {
            ui->frame_Provides->setVisible(true);
        }
        ui->listProvides->clear();
        ui->listProvides->addItems(oldPkg->providesList());
    } else {
        if (ui->frame_Provides->isVisible()) {
            ui->frame_Provides->setVisible(false);
        }
    }

    // Enhances
    if (!oldPkg->enhancesList().isEmpty()) {
        if (!ui->frame_Enhances->isVisible()) {
            ui->frame_Enhances->setVisible(true);
        }
        ui->listEnhances->clear();
        ui->listEnhances->addItems(oldPkg->enhancesList());
    } else {
        if (ui->frame_Enhances->isVisible()) {
            ui->frame_Enhances->setVisible(false);
        }
    }

    // Enhanced by
    if (!oldPkg->enhancedByList().isEmpty()) {
        if (!ui->frame_EnhancedBy->isVisible()) {
            ui->frame_EnhancedBy->setVisible(true);
        }
        ui->listEnhancedBy->clear();
        ui->listEnhancedBy->addItems(oldPkg->enhancedByList());
    } else {
        if (ui->frame_EnhancedBy->isVisible()) {
            ui->frame_EnhancedBy->setVisible(false);
        }
    }

    // Recommends
    if (!oldPkg->recommendsList().isEmpty()) {
        if (!ui->frame_Recommends->isVisible()) {
            ui->frame_Recommends->setVisible(true);
        }
        ui->listRecommends->clear();
        ui->listRecommends->addItems(oldPkg->recommendsList());
    } else {
        if (ui->frame_Recommends->isVisible()) {
            ui->frame_Recommends->setVisible(false);
        }
    }

    // Suggests
    if (!oldPkg->suggestsList().isEmpty()) {
        if (!ui->frame_Suggests->isVisible()) {
            ui->frame_Suggests->setVisible(true);
        }
        ui->listSuggests->clear();
        ui->listSuggests->addItems(oldPkg->suggestsList());
    } else {
        if (ui->frame_Suggests->isVisible()) {
            ui->frame_Suggests->setVisible(false);
        }
    }
}
