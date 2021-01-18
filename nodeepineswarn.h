#ifndef NODEEPINESWARN_H
#define NODEEPINESWARN_H

#include <DDialog>

DWIDGET_USE_NAMESPACE

class NoDeepinesWarn : public DDialog
{
public:
    explicit NoDeepinesWarn();

    void generatePopup();
};

#endif // NODEEPINESWARN_H
