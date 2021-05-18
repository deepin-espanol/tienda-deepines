#include "dynamicressourceloader.h"

#include "ext/libda-release/sharednam.h"
#include <QFile>
#include <QNetworkReply>
#include <QDataStream>
#include <QTimer>

DynamicResourceLoader::DynamicResourceLoader(QObject *parent) : QObject(parent) {}

QNetworkRequest generate(QUrl p)
{
    QNetworkRequest r(p);
    r.setAttribute(QNetworkRequest::Attribute::FollowRedirectsAttribute, true);
    return r;
}

void DynamicResourceLoader::finished()
{
    QByteArray b = _reply->readAll();
    QString result = "/tmp/tienda-deepines/"+_reply->url().toString().replace("://", ":/").replace("/", "%");

    if (result != "/tmp/tienda-deepines/") {
        QFile file(result);
        file.open(QIODevice::WriteOnly);
        QDataStream out(&file);
        file.write(b);
        file.flush();
        file.close();
    } else {
        result = "";
    }
    _reply->deleteLater();

    QList<DynamicResource *> list = pending[_reply->url()];
    int i = 0;
    int len = list.length();

    while (i<len) {
        list[i]->end(result);
        i++;
    }

    if (toprocess == processed) {
        toprocess = 0;
        processed = 0;
        waitingRequests.clear();
        pending.clear();
    }
}

DynamicResource *DynamicResourceLoader::loadRs(QString rs)
{
    DynamicResource *res = new DynamicResource;
    QString cp = rs;
    if (rs.startsWith("file://")) {
        res->delayedEnd(rs.remove(0, 7));
    } else if (QFile("/tmp/tienda-deepines/"+cp.replace("://", ":/").replace("/", "%")).exists() == false) {
        if (waitingRequests.contains(rs) == false) {
            waitingRequests << rs;
            pending[rs] << res;
            toprocess++;
            _reply = Dtk::Addons::SharedNAM::instance()->get(generate(rs));
            connect(_reply, &QNetworkReply::finished, this, &DynamicResourceLoader::finished);
        } else {
            pending[rs] << res;
        }
    } else {
        res->delayedEnd("/tmp/tienda-deepines/"+rs.replace("://", ":/").replace("/", "%"));
    }
    return res;
}

DynamicResource::DynamicResource() : QObject() {}

void DynamicResource::end(QString s)
{
    Q_EMIT finished(s);
}

void DynamicResource::delayedEnd(QString s)
{
    QTimer::singleShot(500, this, [this, s]() {
        Q_EMIT finished(s);
    });
}
