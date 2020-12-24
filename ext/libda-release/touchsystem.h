#ifndef TOUCHSYSTEM_H
#define TOUCHSYSTEM_H

#include "libda_global.h"
#include "swipinggesture.h"

#include <QWidget>
#include <QGesture>

LDA_BEGIN_NAMESPACE

class TouchInterfacing;

class LIBDA_SHARED_EXPORT TouchSystem : public QObject
{
    Q_OBJECT
public:
    explicit TouchSystem();

    inline static TouchSystem *instance() {
        static TouchSystem *inst = new TouchSystem;
        return inst;
    }

    bool eventFilter(QObject *object, QEvent *event) override;
    void listenTo(QWidget *object, Dtk::Addons::TouchInterfacing *face);

    /**
     * @brief Destroys the instance if the interface is no longer existent
     */
    void check();

    /**
     * @brief Prints events data when enabled with UID of the object
     * @param enable
     */
    void enableDebug(bool enable);

    void destroyInterface(Dtk::Addons::TouchInterfacing *face);

protected:
    bool processMouseMove(QMouseEvent *e);
    bool processMousePress(QMouseEvent *e);
    bool processMouseRelease(QMouseEvent *e);
    bool processGestures(QGestureEvent *event);

private:
    QList<Dtk::Addons::TouchInterfacing *> m_interfaces;
    QMap<QWidget *, Dtk::Addons::TouchInterfacing *> m_sources;
    Dtk::Addons::TouchInterfacing *interface;

    bool debug = false;
};

LDA_END_NAMESPACE

#endif // TOUCHSYSTEM_H
