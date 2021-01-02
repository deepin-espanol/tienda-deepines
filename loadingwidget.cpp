#include "loadingwidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <DIconButton>
#include <dwindowclosebutton.h>
#include <DLabel>
#include <QFont>
#include <QApplication>
#include <iostream>

LoadingWidget::LoadingWidget(QWidget *parent) : DBlurEffectWidget(parent)
{
    this->setBlendMode(DBlurEffectWidget::BlendMode::BehindWindowBlend);
    this->setBlurEnabled(true);

    QVBoxLayout *lay = new QVBoxLayout;

    QHBoxLayout *barlay = new QHBoxLayout;
    barlay->setMargin(0);

    DWindowCloseButton *close = new DWindowCloseButton;
    close->setFixedSize(40, 40);
    close->setIconSize(QSize(40, 40));
    DIconButton *btn = new DIconButton(this);
    btn->setIcon(QIcon(":/deepines.svg"));

    DLabel *title = new DLabel;
    QFont f = title->font();
    f.setBold(true);
    title->setFont(f);
    title->setText(qAppName());

    barlay->addWidget(btn, 0, Qt::AlignmentFlag::AlignLeft);
    barlay->addWidget(title, 0, Qt::AlignmentFlag::AlignCenter);
    barlay->addWidget(close, 0, Qt::AlignmentFlag::AlignRight);

    QFrame *frame = new QFrame;
    frame->setLineWidth(0);
    frame->setMaximumHeight(45);
    frame->setLayout(barlay);

    DLabel *mainText = new DLabel(tr("Loading data..."));
    f.setPointSize(18);
    f.setWeight(12);
    mainText->setFont(f);
    mainText->setAlignment(Qt::AlignCenter);

    currentTsk = new DLabel(tr("Loading views"));
    f = currentTsk->font();
    f.setPointSize(10);
    currentTsk->setFont(f);

    bar = new DProgressBar;
    bar->setValue(0);

    lay->addWidget(frame);
    lay->addWidget(mainText);
    lay->addWidget(currentTsk);
    lay->addWidget(bar);

    this->setLayout(lay);

    connect(close, &DWindowCloseButton::clicked, this, &DBlurEffectWidget::close);
}

LoadingWidget::~LoadingWidget()
{
    this->layout()->~QLayout();
}

void LoadingWidget::setCurrentTsk(QString t)
{
    currentTsk->setText(t);
}

void LoadingWidget::updatePercentage(int p)
{
    bar->setValue(p);
}
