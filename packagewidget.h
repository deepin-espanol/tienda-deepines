#ifndef PACKAGEWIDGET_H
#define PACKAGEWIDGET_H

#include "historymanager.h"
#include "bottompackagewidgetinformations.h"

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
    virtual void unload() override;

Q_SIGNALS:
    void reopen(QString pkg);

public Q_SLOTS:
    void reloadUI();
    bool setPackage(QApt::Package *pkg);

private:
    void handleSelfOpen(QModelIndex index, QListWidget *w);
    QApt::Package *oldPkg = nullptr;
    QHBoxLayout *m_layout = nullptr;
    PackageWidgetUI *ui = nullptr;
    BottomPackageWidgetInformations *pkgInfs = nullptr;
};

/* Template structure to add lists to UI
QWidget *$REPLACE_container;
QVBoxLayout *$REPLACE_vl;
QHBoxLayout *$REPLACE_hl;
QLabel *$REPLACE_label;
QFrame *$REPLACE_line;
QListWidget *$REPLACE_list;
*/

/* Template structure to add lists to UI
$REPLACE_container = new QWidget(Form);
$REPLACE_vl = new QVBoxLayout($REPLACE_container);
$REPLACE_vl->setContentsMargins(0, -1, 0, -1);
$REPLACE_hl = new QHBoxLayout();
$REPLACE_hl->setSizeConstraint(QLayout::SetMinimumSize);
$REPLACE_hl->setContentsMargins(-1, 10, -1, -1);
$REPLACE_label = new QLabel($REPLACE_container);
QSizePolicy $REPLACE_sp1(QSizePolicy::Preferred, QSizePolicy::Fixed);
$REPLACE_sp1.setHorizontalStretch(0);
$REPLACE_sp1.setVerticalStretch(0);
$REPLACE_sp1.setHeightForWidth($REPLACE_label->sizePolicy().hasHeightForWidth());
$REPLACE_label->setSizePolicy($REPLACE_sp1);
$REPLACE_label->setFont(font);
$REPLACE_label->setTextInteractionFlags(Qt::NoTextInteraction);
$REPLACE_hl->addWidget($REPLACE_label);
$REPLACE_line = new QFrame($REPLACE_container);
QSizePolicy $REPLACE_sp2(QSizePolicy::Expanding, QSizePolicy::Fixed);
$REPLACE_sp2.setHorizontalStretch(0);
$REPLACE_sp2.setVerticalStretch(0);
$REPLACE_sp2.setHeightForWidth($REPLACE_line->sizePolicy().hasHeightForWidth());
$REPLACE_line->setSizePolicy($REPLACE_sp2);
$REPLACE_line->setFrameShape(QFrame::HLine);
$REPLACE_line->setFrameShadow(QFrame::Sunken);
$REPLACE_hl->addWidget($REPLACE_line);
$REPLACE_vl->addLayout($REPLACE_hl);
$REPLACE_list = new QListWidget($REPLACE_container);
$REPLACE_list->setMinimumSize(QSize(0, 100));
$REPLACE_list->setMaximumSize(QSize(16777215, 280));
$REPLACE_list->setFrameShape(QFrame::NoFrame);
$REPLACE_vl->addWidget($REPLACE_list);
verticalLayout_6->addWidget($REPLACE_container);
*/

/* Template structure to add lists to UI
$REPLACE_label->setText(QApplication::translate("Form", "Dependencies", nullptr));
*/


#endif // PACKAGEWIDGET_H
