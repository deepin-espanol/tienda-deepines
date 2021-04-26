#ifndef DADDONAPPLICATION_H
#define DADDONAPPLICATION_H

#include "libda_global.h"
#include <DApplication>

/**
 * @brief Provides signal handling and open funcs of DApplication.
 */

LDA_BEGIN_NAMESPACE

class LIBDA_SHARED_EXPORT DAddonApplication : public Dtk::Widget::DApplication
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit DAddonApplication(int &argc, char **argv);
    ~DAddonApplication() override;

    /**
     * @brief handleQuitAction, triggered to exit in the right menu of D*Bar
     */
    Q_INVOKABLE void handleQuitAction() override;
    /**
     * @brief handleHelpAction, shows the manual section dedicated to this app
     */
    Q_INVOKABLE void handleHelpAction() override;
    /**
     * @brief handleAboutAction, shows the about popup
     */
    Q_INVOKABLE void handleAboutAction() override;

    /**
     * @brief Are the over FXs on?
     * @return Returns if the hover effects are possible in the whole app (not disabled)
     */
    Q_INVOKABLE bool areHoverEffectsEnabled();
    /**
     * @brief Enable or don't the hover effects in the whole app
     * @param enable
     */
    Q_INVOKABLE void setEnabledHoverEffects(bool enable);
    /**
     * @brief Toggle if the effects have to be enabled or not
     */
    Q_INVOKABLE void toggleHoverEffects();
};

LDA_END_NAMESPACE

#endif // DADDONAPPLICATION_H
