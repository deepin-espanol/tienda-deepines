#ifndef COVERLIST_H
#define COVERLIST_H

#include "ext/libda-release/basicelements.h"
#include <QListWidget>

LDA_USE_NAMESPACE

class QNetworkReply;

class CoverListItem : public Widget
{
    Q_OBJECT
    Q_PROPERTY(QString text WRITE setText NOTIFY textChanged)
public:
    explicit CoverListItem();
    inline virtual QObject *self() override {return (QObject*)this;}

    Q_SIGNAL void textChanged(QString);

public Q_SLOTS:
    void setText(QString);
    void handleResponse(QString p);

protected:
    void paintEvent(QPaintEvent *e) override;
    virtual void enterEvent(QEvent *e) override;
    virtual void leaveEvent(QEvent *e) override;
    virtual void mouseReleaseEvent(QMouseEvent *e) override;

private:
    QPixmap img;
    QPixmap blurred;
    bool hasLoaded = false;
    bool hovered = false;
    QNetworkReply *ans;
    QString m_name = "";
};


class CoverList : public QListWidget, public AbstractElement
{
    Q_OBJECT
public:
    explicit CoverList();
    inline virtual QObject *self() override {return this;}
    virtual void addElement(AbstractElement *element) override;
};

#endif // COVERLIST_H
