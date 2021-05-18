#ifndef SHAREDNM_H
#define SHAREDNM_H

#include "class_decl.h"
#include "libda_global.h"

#include <QtNetwork/QNetworkAccessManager>

LDA_BEGIN_NAMESPACE

/**
 * @brief Memory shared QNAM for multi-purpose
 */
class LIBDA_SHARED_EXPORT SharedNAM : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit SharedNAM(QObject *p = nullptr);
    /**
     * @brief Synchronous network request (in opposition to QNetworkAccessManager::get)
     * @param msTimeout
     * @return The received QNetworkReply
     */
    QNetworkReply *pendingGet(const QNetworkRequest &, int msTimeout = 5000);
    static SharedNAM *instance();
};

LDA_END_NAMESPACE

#endif // SHAREDNM_H
