#ifndef PACKAGEWIDGET_H
#define PACKAGEWIDGET_H

#include "abstracthistoryhandler.h"

#include <QScrollArea>
#include <qapt/package.h>
#include <QHBoxLayout>

class QListWidget;
class PackageWidgetUI;

class PackageWidget : public QScrollArea, public AbstractHistoryHandler
{
    Q_OBJECT
public:
    explicit PackageWidget(QWidget *parent = nullptr);
    ~PackageWidget() override;
    inline virtual QWidget *widget() const override {return (QWidget*)(this);}
    virtual void load(QString) override;

Q_SIGNALS:
    void reopen(QString pkg);

public Q_SLOTS:
    void reloadUI();
    void setPackage(QApt::Package *pkg);

private:
    void handleSelfOpen(QModelIndex index, QListWidget *w);
    QApt::Package *oldPkg = nullptr;
    QHBoxLayout *m_layout = nullptr;
    PackageWidgetUI *ui = nullptr;
};

/*
    QListWidget *list$UID;
    QFrame *frame_$UID;
    QVBoxLayout *verticalLayout_$UID;
    QHBoxLayout *horizontalLayout_$UID;
    QLabel *label_$UID;
    QFrame *line_$UID;

    frame_$UID = new QFrame(Form);
    frame_$UID->setObjectName(QStringLiteral("frame_$UID"));
    frame_$UID->setFrameShape(QFrame::StyledPanel);
    frame_$UID->setFrameShadow(QFrame::Raised);
    verticalLayout_$UID = new QVBoxLayout(frame_$UID);
    verticalLayout_$UID->setObjectName(QStringLiteral("verticalLayout_$UID"));
    verticalLayout_$UID->setContentsMargins(0, -1, 0, -1);
    horizontalLayout_$UID = new QHBoxLayout();
    horizontalLayout_$UID->setObjectName(QStringLiteral("horizontalLayout_$UID"));
    horizontalLayout_$UID->setContentsMargins(-1, 0, -1, -1);
    label_$UID = new QLabel(frame_$UID);
    label_$UID->setObjectName(QStringLiteral("label_$UID"));
    QSizePolicy sizePolicy$UID(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy$UID.setHorizontalStretch(0);
    sizePolicy$UID.setVerticalStretch(0);
    sizePolicy$UID.setHeightForWidth(label_$UID->sizePolicy().hasHeightForWidth());
    label_$UID->setSizePolicy(sizePolicy$UID);
    label_$UID->setFont(font);
    label_$UID->setTextInteractionFlags(Qt::NoTextInteraction);

    horizontalLayout_$UID->addWidget(label_$UID);

    line_$UID = new QFrame(frame_$UID);
    line_$UID->setObjectName(QStringLiteral("line_$UID"));
    sizePolicy1.setHeightForWidth(line_$UID->sizePolicy().hasHeightForWidth());
    line_$UID->setSizePolicy(sizePolicy1);
    line_$UID->setFrameShape(QFrame::HLine);
    line_$UID->setFrameShadow(QFrame::Sunken);

    horizontalLayout_$UID->addWidget(line_$UID);


    verticalLayout_$UID->addLayout(horizontalLayout_$UID);

    list$UID = new QListWidget(frame_$UID);
    list$UID->setObjectName(QStringLiteral("list$UID"));

    verticalLayout_$UID->addWidget(list$UID);


    verticalLayout_6->addWidget(frame_$UID);
    */

#endif // PACKAGEWIDGET_H
