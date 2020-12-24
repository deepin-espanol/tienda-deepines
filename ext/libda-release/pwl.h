#ifndef PWL_H
#define PWL_H

#include "libda_global.h"
#include <QObject>

LDA_BEGIN_NAMESPACE

/**
 * @brief PWL class is used to track windows of a given process,
 * you can use it to embed an external window to your own.
 */
class LIBDA_SHARED_EXPORT PWL : public QObject
{
    Q_OBJECT
public:
    explicit PWL(QObject *parent = nullptr);
    ~PWL();
    QList<int> WinIDs();

Q_SIGNALS:
    /**
     * @brief A window from the process have been added
     * @param id
     */
    void windowAdded(int id);
    /**
     * @brief A window from the process have been closed (Removed)
     * @param id
     */
    void windowRemoved(int id);

public Q_SLOTS:
    /**
     * @brief Change the PID to track for its windows
     * @param pid
     */
    void setPID(int pid = 0);

private:
    int m_pid = 0;
    QList<int> m_ids;
};

LDA_END_NAMESPACE

#endif // PWL_H
