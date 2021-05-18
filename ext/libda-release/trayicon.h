#ifndef TRAYICON_H
#define TRAYICON_H

#include "libda_global.h"
#include <QtWidgets>

LDA_BEGIN_NAMESPACE

/**
 * @brief The TrayIcon class
 */
class LIBDA_SHARED_EXPORT TrayIcon : public QObject
{
    Q_OBJECT
public:
    explicit TrayIcon(QObject *parent = nullptr);
    ~TrayIcon();

    /**
     * @brief Get the tray menu being used.
     * @return The menu
     */
    QMenu *trayMenu();
    /**
     * @brief Get tray's title.
     * @return The title
     */
    QString trayTitle();
    QIcon trayIcon();
    bool isTrayVisible();

public Q_SLOTS:
    /**
     * @brief Change the tray's icon.
     * @param icon
     */
    void setTrayIcon(QIcon icon);
    /**
     * @brief Change the tray's title.
     * @param str
     */
    void setTrayTitle(QString str);
    /**
     * @brief Change the tray's menu to another one.
     * @param m
     */
    void setTrayMenu(QMenu *m);
    /**
     * @brief Enable or disable if the menu has to be shown.
     * @param enable
     */
    void enableContextMenu(bool enable);
    /**
     * @brief Change tray's visibility.
     * @param visible
     */
    void setTrayVisible(bool visible);
    /**
     * @brief Handles tray's activations.
     * @param reason
     */
    virtual void iconActivated(QSystemTrayIcon::ActivationReason reason);

Q_SIGNALS:
    /**
     * @brief Emitted on tray icon click.
     */
    void clicked();

private:
    QSystemTrayIcon *m_trayIcon;
    QMenu *m_menu;
    bool enabled = true;
};

LDA_END_NAMESPACE

#endif // TRAYICON_H
