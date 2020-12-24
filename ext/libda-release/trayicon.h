#ifndef TRAYICON_H
#define TRAYICON_H

#include "libda_global.h"
#include <QtWidgets>

LDA_BEGIN_NAMESPACE

class LIBDA_SHARED_EXPORT TrayIcon : public QObject
{
    Q_OBJECT
public:
    explicit TrayIcon(QObject *parent = nullptr);
    ~TrayIcon();

    QMenu *trayMenu();
    QString trayTitle();
    QIcon trayIcon();
    bool isTrayVisible();

public Q_SLOTS:
    void setTrayIcon(QIcon icon);
    void setTrayTitle(QString str);
    void setTrayMenu(QMenu *m);
    void enableContextMenu(bool enable);
    void setTrayVisible(bool visible);
    virtual void iconActivated(QSystemTrayIcon::ActivationReason reason);

Q_SIGNALS:
    void clicked();

private:
    QSystemTrayIcon *m_trayIcon;
    QMenu *m_menu;
    bool enabled = true;
};

LDA_END_NAMESPACE

#endif // TRAYICON_H
