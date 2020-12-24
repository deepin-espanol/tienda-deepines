#ifndef LOADINGWIDGET_H
#define LOADINGWIDGET_H

#include <DBlurEffectWidget>
#include <DProgressBar>
#include <DLabel>

DWIDGET_USE_NAMESPACE

class LoadingWidget : public DBlurEffectWidget
{
    Q_OBJECT
public:
    explicit LoadingWidget(QWidget *parent = nullptr);
    ~LoadingWidget();
    void updatePercentage(int p);
    void setCurrentTsk(QString t);

private:
    DLabel *currentTsk = nullptr;
    DProgressBar *bar = nullptr;
};

#endif // LOADINGWIDGET_H
