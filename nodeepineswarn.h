#ifndef NODEEPINESWARN_H
#define NODEEPINESWARN_H

#include <DDialog>

DWIDGET_USE_NAMESPACE

/**
 * @brief Popup to warn user for possible incompatibilities while DEE repos aren't installed
 */
class NoDeepinesWarn : public DDialog
{
public:
    explicit NoDeepinesWarn();

    void generatePopup();
};

#endif // NODEEPINESWARN_H
