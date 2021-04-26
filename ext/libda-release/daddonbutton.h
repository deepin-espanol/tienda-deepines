#ifndef DADDONICONBUTTON_H
#define DADDONICONBUTTON_H

#include "libda_global.h"

#include <QMenu>
#include <DIconButton>

LDA_BEGIN_NAMESPACE

/**
 * @brief The DAddonIconButton class, special kit for menu popups
 */
class LIBDA_SHARED_EXPORT DAddonIconButton : public Dtk::Widget::DIconButton
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit DAddonIconButton(QWidget *parent = nullptr, Qt::AnchorPoint xa = Qt::AnchorLeft, Qt::AnchorPoint ya = Qt::AnchorBottom);
    Q_INVOKABLE ~DAddonIconButton();

    /**
     * @brief processAnchor, XY to use depending of the anchor (relative to this button). Not all are handled!
     * @param a
     * @return int
     */
    Q_INVOKABLE int processAnchor(Qt::AnchorPoint a);
    /**
     * @brief anchorX, X anchor used to set pos when popuping the menu
     * @return Qt::AnchorPoint
     */
    Q_INVOKABLE Qt::AnchorPoint anchorX() const;
    /**
     * @brief anchorY, Y anchor used to set pos when popuping the menu
     * @return Qt::AnchorPoint
     */
    Q_INVOKABLE Qt::AnchorPoint anchorY() const;

Q_SIGNALS:
    /**
     * @brief clicked
     */
    void clicked();
    /**
     * @brief requestMenu, emitted when clicked, if you need to use a QMenu
     */
    void requestMenu();

public Q_SLOTS:
    /**
     * @brief setMenuXAnchor set the X menu's anchor when it'll be displayed
     * @param a
     */
    void setMenuXAnchor(Qt::AnchorPoint a);
    /**
     * @brief setMenuYAnchor, set the Y menu's anchor when it'll be displayed
     * @param a
     */
    void setMenuYAnchor(Qt::AnchorPoint a);
    /**
     * @brief setMenuAnchors, set the X & Y menu's anchors when it'll be displayed
     * @param x
     * @param y
     */
    void setMenuAnchors(Qt::AnchorPoint x, Qt::AnchorPoint y);
    /**
     * @brief handleMenuRequest, calling this shows the menu, call it in response to @requestMenu()
     * @param menu
     */
    void handleMenuRequest(QMenu *menu);

private:
    Qt::AnchorPoint anchor_x;
    Qt::AnchorPoint anchor_y;
};

LDA_END_NAMESPACE

#endif // DADDONICONBUTTON_H
