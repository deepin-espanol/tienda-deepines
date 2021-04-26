#ifndef DSPLITEDBAR_H
#define DSPLITEDBAR_H

#include "libda_global.h"

#include <dtkwidget_global.h>
#include <DGuiApplicationHelper>

#include <DObjectPrivate>

#include <dwindowclosebutton.h>
#include <dwindowmaxbutton.h>
#include <dwindowminbutton.h>
#include <dwindowoptionbutton.h>
#include <dwindowquitfullbutton.h>
#include <dplatformwindowhandle.h>
#include <daboutdialog.h>
#include <dapplication.h>
#include <dmainwindow.h>
#include <DHorizontalLine>
#include <dimagebutton.h>
#include <dblureffectwidget.h>
#include <dwidgetstype.h>
#include <dlabel.h>

#include <QMenu>
#include <QFrame>

class QHBoxLayout;
class QTimer;

LDA_BEGIN_NAMESPACE

DGUI_USE_NAMESPACE
DWIDGET_USE_NAMESPACE

class DAddonSplittedWindow;
class DAddonSplittedBarPrivate;

/**
 * @brief Modern splitted bar for DAddonSplittedWindow or others classes.
 */

class LIBDA_SHARED_EXPORT DAddonSplittedBar : public QFrame, public DTK_CORE_NAMESPACE::DObject
{
    Q_OBJECT
    Q_PROPERTY(bool blurBackground READ blurBackground WRITE setBlurBackground)
    Q_PROPERTY(int buttonAreaWidth READ buttonAreaWidth)
    Q_PROPERTY(int leftMargin READ leftMargin WRITE setLeftMargin)
    Q_PROPERTY(bool switchThemeMenuVisible READ switchThemeMenuIsVisible WRITE setSwitchThemeMenuVisible)
    Q_PROPERTY(bool isMenuVisible READ menuIsVisible WRITE setMenuVisible)
    Q_PROPERTY(bool isMenuDisabled READ menuIsDisabled WRITE setMenuDisabled)
    Q_PROPERTY(bool autoHideOnFullscreen READ autoHideOnFullscreen WRITE setAutoHideOnFullscreen)
    Q_PROPERTY(bool quitMenuIsDisabled READ quitMenuIsDisabled WRITE setQuitMenuDisabled)

public:
    explicit DAddonSplittedBar(QWidget *parent = Q_NULLPTR);
    ~DAddonSplittedBar();

#ifndef QT_NO_MENU
    /**
     * @brief menu, menu of the right, classic DDE style menu
     * @return Menu at right (options)
     */
    Q_INVOKABLE QMenu *menu() const;
    /**
     * @brief leftMenu, the menu of the left, addons that uses the app icon
     * @return Menu of the left side button (icon)
     */
    Q_INVOKABLE QMenu *leftMenu() const;
    /**
     * @brief setLeftMenu, use another menu for the left instead of the default one
     * @param menu
     */
    Q_INVOKABLE void setLeftMenu(QMenu *menu);
    /**
     * @brief setMenu, use another menu on the right instead of the default one
     * @param menu
     */
    Q_INVOKABLE void setMenu(QMenu *menu);
#endif

    /**
     * @brief Custom widget of the bar
     * @return The widget of the bar (middle)
     */
    Q_INVOKABLE QWidget *customWidget() const;
    /**
     * @brief Sets the cutom widget to be used (instead of the win's title)
     * @param widget
     * @param fixCenterPos
     */
    Q_INVOKABLE void setCustomWidget(QWidget *widget, bool fixCenterPos = false);

    /**
     * @brief Add a widget to the bar's layout
     * @param w
     * @param alignment
     */
    Q_INVOKABLE void addWidget(QWidget *w, Qt::Alignment alignment = Qt::Alignment());
    /**
     * @brief Remove widget w of the bar
     * @param w
     */
    Q_INVOKABLE void removeWidget(QWidget *w);

    /**
     * @brief Width of the bar's button area
     * @return
     */
    int buttonAreaWidth() const;
    /**
     * @brief The visibility of the separator used in the bar
     * @return
     */
    bool separatorVisible() const;

    /**
     * @brief Hides when the targ win is maximized
     * @return
     */
    bool autoHideOnFullscreen() const;
    /**
     * @brief Must or not be hidden in maximized
     * @param autohide
     */
    void setAutoHideOnFullscreen(bool autohide);

    /**
     * @brief Bar's visibility
     * @param visible
     */
    void setVisible(bool visible) Q_DECL_OVERRIDE;
    /**
     * @brief Hides some components when set on true
     * @param embed
     */
    void setEmbedMode(bool embed);

    /**
     * @brief Should the right side menu be visible
     * @return
     */
    bool menuIsVisible() const;
    /**
     * @brief Hide or not the right side menu
     * @param visible
     */
    void setMenuVisible(bool visible);

    /**
     * @brief Right menu is disabled or not
     * @return
     */
    bool menuIsDisabled() const;
    /**
     * @brief Must or not the right side menu be disabled
     * @param disabled
     */
    void setMenuDisabled(bool disabled);

    /**
     * @brief Quit option(s) have to be disabled
     * @return
     */
    bool quitMenuIsDisabled() const;
    /**
     * @brief Should the Quit option(s) be disabled
     * @param disabled
     */
    void setQuitMenuDisabled(bool disabled);
    /**
     * @brief Should the Quit option(s) be shown
     * @param visible
     */
    void setQuitMenuVisible(bool visible);

    /**
     * @brief switchThemeMenuIsVisible
     * @return
     */
    bool switchThemeMenuIsVisible() const;
    /**
     * @brief setSwitchThemeMenuVisible
     * @param visible
     */
    void setSwitchThemeMenuVisible(bool visible);

    /**
     * @brief Flag(s) that must be disabled
     * @param flags
     */
    void setDisableFlags(Qt::WindowFlags flags);
    /**
     * @brief Remove all flags currently used
     * @return Flag(s) being disabled
     */
    Qt::WindowFlags disableFlags() const;

    /**
     * @brief sizeHint
     * @return
     */
    QSize sizeHint() const override;
    /**
     * @brief minimumSizeHint
     * @return
     */
    QSize minimumSizeHint() const override;

    /**
     * @brief bkgd is blurred?
     * @return Wether or not the bkgd be blurred or solid
     */
    bool blurBackground() const;

    /**
     * @brief leftMargin
     * @return
     */
    int leftMargin();
    /**
     * @brief setLeftMargin
     * @param margin
     */
    void setLeftMargin(int margin);

    /**
     * @brief Is the titlebar auto-hiding itself
     * @return
     */
    bool isAutoHidden() const;

    Q_INVOKABLE QHBoxLayout *leftLayout() const;
    Q_INVOKABLE QHBoxLayout *centerLayout() const;
    Q_INVOKABLE QHBoxLayout *rightLayout() const;

Q_SIGNALS:
    /**
     * @brief optionClicked
     */
    void optionClicked();
    /**
     * @brief doubleClicked
     */
    void doubleClicked();
    /**
     * @brief mousePressed
     * @param buttons
     */
    void mousePressed(Qt::MouseButtons buttons);
    /**
     * @brief mouseMoving
     * @param button
     */
    void mouseMoving(Qt::MouseButton button);
    /**
     * @brief Sent when window is maximized (after resizing to fill the area(s))
     */
    void setupMaximizedSettings();

#ifdef DTK_TITLE_DRAG_WINDOW
    void mousePosPressed(Qt::MouseButtons buttons, QPoint pos);
    void mousePosMoving(Qt::MouseButton button, QPoint pos);
#endif

public Q_SLOTS:
    /**
     * @brief setFixedHeight
     * @param h
     */
    void setFixedHeight(int h);
    /**
     * @brief setBackgroundTransparent
     * @param transparent
     */
    void setBackgroundTransparent(bool transparent);
    /**
     * @brief setSeparatorVisible
     * @param visible
     */
    void setSeparatorVisible(bool visible);
    /**
     * @brief setTitle
     * @param title
     */
    void setTitle(const QString &title);
    /**
     * @brief setIcon
     * @param icon
     */
    void setIcon(const QIcon &icon);
    /**
     * @brief Maximized/Minimized win state
     */
    void toggleWindowState();
    /**
     * @brief Set the menu of the left side
     * @param iconMenu
     */
    void setIconMenu(QMenu *iconMenu);
    /**
     * @brief Set if the background have to be blurred
     * @param blurBackground
     */
    void setBlurBackground(bool blurBackground);
    /**
     * @brief Set align you want for the title
     */
    void setCustomTitleAlign(Qt::Alignment);

private Q_SLOTS:
#ifndef QT_NO_MENU
    void showMenu();
    void showIconMenu();
#endif

protected:
    bool eventFilter(QObject *obj, QEvent *event) Q_DECL_OVERRIDE;
    bool event(QEvent *e) override;
    void showEvent(QShowEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void enterEvent(QEvent *e) override;
    void leaveEvent(QEvent *e) override;

    void slideDown();
    void slideUp();

private:
    int left_margin = 250;
    bool isFirstMarginSet = true;
    bool isHidden = false;
    bool isMaximized = false;
    QMenu *m_iconMenu;
    int oldHeight = 40;

    QColor getColor();

    QTimer *logic;
    bool runingAnim = false;

    D_DECLARE_PRIVATE(DAddonSplittedBar)
    D_PRIVATE_SLOT(void _q_toggleWindowState())
    D_PRIVATE_SLOT(void _q_showMinimized())
    D_PRIVATE_SLOT(void _q_onTopWindowMotifHintsChanged(quint32))

#ifndef QT_NO_MENU
    D_PRIVATE_SLOT(void _q_addDefaultMenuItems())
    D_PRIVATE_SLOT(void _q_helpActionTriggered())
    D_PRIVATE_SLOT(void _q_aboutActionTriggered())
    D_PRIVATE_SLOT(void _q_quitActionTriggered())
    D_PRIVATE_SLOT(void _q_switchThemeActionTriggered(QAction*))
#endif
};

class DAddonSplittedBarPrivate : public DTK_CORE_NAMESPACE::DObjectPrivate
{
protected:
    DAddonSplittedBarPrivate(DAddonSplittedBar *qq);

private:
    void init();
    QWidget *targetWindow();
    QWidget *titleSource;
    // FIXME: get a batter salution
    // hide title will make eventFilter not work, instead set Height to zero
    bool isVisableOnFullscreen();
    void hideOnFullscreen();
    void showOnFullscreen();

    void updateFullscreen();
    void updateButtonsState(Qt::WindowFlags type);
    void updateButtonsFunc();
    void updateCenterArea();

    void handleParentWindowStateChange();
    void handleParentWindowIdChange();
    void _q_toggleWindowState();
    void _q_showMinimized();
    void _q_onTopWindowMotifHintsChanged(quint32 winId);

    //Used to handle maximize/fullscreen titlebar hiding
    void handleMaximizingPreparation();

#ifndef QT_NO_MENU
    void _q_addDefaultMenuItems();
    void _q_helpActionTriggered();
    void _q_aboutActionTriggered();
    void _q_quitActionTriggered();
    void _q_switchThemeActionTriggered(QAction*action);
#endif

    void setIconVisible(bool visible);
    void updateTabOrder();

    QHBoxLayout         *mainLayout;
    QWidget             *leftArea;
    QHBoxLayout         *leftLayout;
    QWidget             *rightArea;
    QHBoxLayout         *rightLayout;
    DLabel              *centerArea;
    QHBoxLayout         *centerLayout;
    DIconButton         *iconLabel;
    QWidget             *buttonArea;
    DWindowMinButton    *minButton;
    DWindowMaxButton    *maxButton;
    DWindowCloseButton  *closeButton;
    DWindowOptionButton *optionButton;
    DWindowQuitFullButton *quitFullButton;
    DLabel              *titleLabel;
    QWidget             *customWidget = nullptr;

    DHorizontalLine     *separatorTop;
    DHorizontalLine     *separator;

    DBlurEffectWidget   *blurWidget = nullptr;

#ifndef QT_NO_MENU
    QMenu               *menu             = Q_NULLPTR;
    QAction             *helpAction       = Q_NULLPTR;
    QAction             *aboutAction      = Q_NULLPTR;
    QAction             *quitAction       = Q_NULLPTR;
    bool                canSwitchTheme    = true;
    QAction             *themeSeparator   = nullptr;
    QMenu               *switchThemeMenu  = nullptr;
    QAction             *autoThemeAction  = nullptr;
    QAction             *lightThemeAction = nullptr;
    QAction             *darkThemeAction  = nullptr;
    QMenu               *automateIconMenu();
    QMenu               *m_iconmenu       = nullptr;
#endif

    QWindow            *targetWindowHandle = Q_NULLPTR;

    Qt::WindowFlags     disableFlags;
    bool                mousePressed    = false;
    bool                embedMode       = false;
    bool                autoHideOnFullscreen = false;

    Q_DECLARE_PUBLIC(DAddonSplittedBar)
};

LDA_END_NAMESPACE

#endif // DSPLITEDBAR_H
