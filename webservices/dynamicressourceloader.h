#ifndef DYNAMICRESSOURCELOADER_H
#define DYNAMICRESSOURCELOADER_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <DSingleton>

class DynamicResourceLoader;

class DynamicResource : public QObject
{
    Q_OBJECT
public:
    explicit DynamicResource();

Q_SIGNALS:
    void finished(QString);

protected Q_SLOTS:
    void end(QString s);
    void delayedEnd(QString s);

private:
    friend class DynamicResourceLoader;
};

class DynamicResourceLoader : public QObject, public Dtk::Core::DSingleton<DynamicResourceLoader>
{
    Q_OBJECT
public:
    explicit DynamicResourceLoader(QObject *parent = nullptr);

    DynamicResource *loadRs(QString url);

public Q_SLOTS:
    void finished();

private:
    QList<QUrl> waitingRequests;
    QMap<QUrl, QList<DynamicResource *>> pending;
    QNetworkRequest request;
    QNetworkReply *_reply;
    int toprocess = 0;
    int processed = 0;
};

#endif // DYNAMICRESSOURCELOADER_H
