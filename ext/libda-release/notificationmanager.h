#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include "libda_global.h"
#include <QDBusAbstractInterface>
#include <QDBusPendingReply>

LDA_BEGIN_NAMESPACE

/**
 * @brief QObject representation of a notification (Freedesktop-compliant)
 */
class LIBDA_SHARED_EXPORT NotificationObject : public QObject
{
    Q_OBJECT
public:
    explicit NotificationObject(QObject *parent = nullptr);
    ~NotificationObject();

    /**
     * @brief Change notification's summary
     * @param sum
     * @return
     */
    NotificationObject *setSummary(QString sum);
    /**
     * @brief Change the notification's body
     * @param body
     * @return itself
     */
    NotificationObject *setBody(QString body);
    /**
     * @brief Set the (visible) app name that sent the notification.
     * @param appName
     * @return
     */
    NotificationObject *setApp(QString appName);
    /**
     * @brief Change application's icon name
     * @param iconName
     * @return
     */
    NotificationObject *setAppIcon(QString iconName);
    /**
     * @brief Set actions' names
     * @param actions
     * @return
     */
    NotificationObject *setActions(QStringList actions);
    /**
     * @brief Set actions' IDs
     * @param actIDs
     * @return
     */
    NotificationObject *setActionIDs(QStringList actIDs);
    /**
     * @brief Set raw actions' values: {Name, ID, Name, ID...}
     * @param rawActions
     * @return
     */
    NotificationObject *setRawActions(QStringList rawActions);
    /**
     * @brief Change the visibility duration of the notification (-1 is system's default timeout)
     * @param t
     * @return
     */
    NotificationObject *setTimeout(int t = -1);

    /**
     * @brief Mix up of addAction(QString) and addActionIdentifier(QString), recommended
     * @param identifier
     * @param text
     * @return
     */
    NotificationObject *addAction(QString identifier = "", QString text = "action");
    /**
     * @brief Add an action entry
     * @param text
     * @return
     */
    NotificationObject *addAction(QString text);
    /**
     * @brief Add an action entry's ID
     * @param id
     * @return
     */
    NotificationObject *addActionIdentifier(QString id);

    /**
     * @brief Notification manager that handles this notification
     * @return
     */
    NotificationManager *manager() const;
    /**
     * @brief Get notification's ID
     * @return
     */
    uint id();
    /**
     * @brief Get the notification's timeout
     * @return
     */
    int timeout();
    /**
     * @brief Get the notification'summary
     * @return
     */
    QString summary();
    /**
     * @brief Get the notification's body
     * @return
     */
    QString body();
    /**
     * @brief Get the notification's application name
     * @return
     */
    QString appName();
    /**
     * @brief appIcon
     * @return
     */
    QString appIcon();
    /**
     * @brief Retrieves raw actions: {Name, ID, Name, ID... }
     * @return
     */
    QStringList rawActions();
    /**
     * @brief Retrieves the actions set (their names)
     * @return
     */
    QStringList actions();
    /**
     * @brief Retrieves the actions' IDs
     * @return
     */
    QStringList actionIDs();

    /**
     * @brief Close the notification
     */
    void close();

Q_SIGNALS:
    /**
     * @brief Action of ID identifier have been triggered by user.
     * @param identifier
     */
    void actionTriggered(QString identifier);
    /**
     * @brief User closed the notification.
     */
    void closed();

private:
    NotificationManager *m_manager;
    uint m_id = 0;
    int m_timeout = -1;
    QString m_summary = "";
    QString m_body = "";
    QString m_app = "";
    QString m_appIcon = "";
    QStringList m_actions;
    QStringList m_actionIDs;

    QStringList mergeAAI();
    void unMergeRaw(QStringList raw);

    friend class NotificationManager;
};

class NotificationsInterface : public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.freedesktop.Notifications"; }

public:
    NotificationsInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = nullptr);
    ~NotificationsInterface();

public Q_SLOTS:
    QDBusPendingReply<> CloseNotification(uint in0);
    QDBusPendingReply<uint> Notify(const QString &in0, uint in1, const QString &in2, const QString &in3, const QString &in4, const QStringList &in5, const QVariantMap &in6, int in7);

Q_SIGNALS:
    inline void ActionInvoked(uint in0, const QString &in1);
    inline void NotificationClosed(uint in0, uint in1);
};

class LIBDA_SHARED_EXPORT NotificationManager : public QObject
{
    Q_OBJECT
public:
    explicit NotificationManager(QObject *parent = nullptr);
    inline static NotificationManager *instance() {
        static NotificationManager *inst = new NotificationManager;
        return inst;
    }
    NotificationObject *notify(QString appName, QString appIcon, QString summary, QString body, QStringList actions, QStringList actionIDs, int timeout) const;
    NotificationObject *notify(QString appName, QString appIcon, QString summary, QString body, QStringList rawActions, int timeout) const;
    NotificationObject *notify(NotificationObject *o) const;

    void handleCloseRequest(uint id);

Q_SIGNALS:
    void dataTriggered(QString ID);

protected:
    QList<NotificationObject *> *internList;
    NotificationsInterface *interface;

private Q_SLOTS:
    void handleClosed(uint a, uint b);
    void handleActionTriggered(uint id, QString ID);
};

LDA_END_NAMESPACE

#endif // NOTIFICATIONMANAGER_H
