#ifndef COVERLIST_H
#define COVERLIST_H

#include "ext/libda-release/basicelements.h"
#include <QListWidget>

LDA_USE_NAMESPACE

class QNetworkReply;

class CoverListItem : public QObject, public AbstractElement
{
    Q_OBJECT
    Q_PROPERTY(QString text WRITE setText NOTIFY textChanged)
public:
    explicit CoverListItem();
    inline virtual QObject *self() override {return (QObject *)this;}
    inline virtual ~CoverListItem() override {}
    inline virtual void addElement(AbstractElement *) override {}

    Q_SIGNAL void textChanged(QString);

    QPixmap img;
    QPixmap blurred;
    bool hasLoaded = false;
    QString m_name = " ";

public Q_SLOTS:
    void setText(QString);
    void handleResponse(QString p);

private:
    QNetworkReply *ans;
};

struct Delegate;
typedef QMap<QString, CoverListItem *> REFF;

class CoverList : public QListWidget, public AbstractElement
{
    Q_OBJECT
public:
    explicit CoverList();
    inline virtual QObject *self() override {return this;}
    virtual void addElement(AbstractElement *element) override;

protected:
    Delegate *delegate;
    REFF *references;
};

#endif // COVERLIST_H
