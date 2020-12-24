#ifndef SHAREDNM_H
#define SHAREDNM_H

#include "class_decl.h"
#include "libda_global.h"

#include <QtNetwork/QNetworkAccessManager>

LDA_BEGIN_NAMESPACE

class LIBDA_SHARED_EXPORT SharedNAM : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit SharedNAM(QObject *p = nullptr);
    QNetworkReply *pendingGet(const QNetworkRequest &);
    static SharedNAM *instance();
};

LDA_END_NAMESPACE

#endif // SHAREDNM_H
