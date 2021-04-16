#ifndef ICONLIST_H
#define ICONLIST_H

#include "ext/libda-release/abstractelement.h"

#include <QListWidget>
#include <QListWidgetItem>

LDA_USE_NAMESPACE

/**
 * @brief IconListItem represents an item of IconList XWE UI Element
 */
class IconListItem : public QObject, public AbstractElement
{
    Q_OBJECT
public:
    explicit IconListItem();
    inline virtual QObject *self() override {return this;}
    inline virtual void addElement(AbstractElement *) override {}
};

/**
 * @brief IconList's and CoverList's viewport widget class
 */
class ViewPort : public QWidget
{
    Q_OBJECT
public:
    explicit ViewPort();

protected:
    void paintEvent(QPaintEvent *e) override;
};

/**
 * @brief List of apps with text and icons XWE UI ELement
 */
class IconList : public QListWidget, public AbstractElement
{
    Q_OBJECT
public:
    explicit IconList();
    inline virtual QObject *self() override {return this;}
    virtual void addElement(AbstractElement *element) override;
};

#endif // ICONLIST_H
