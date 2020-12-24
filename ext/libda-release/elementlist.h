#ifndef ELEMENTLIST_H
#define ELEMENTLIST_H

#include "libda_global.h"
#include <QListWidget>
#include <QDrag>
#include <QMimeData>
#include <QPainter>

LDA_BEGIN_NAMESPACE
class Element;

/**
 * @brief ElementList holds QWidgets and derivates, primary for Element[s] from  this lib
 */
class LIBDA_SHARED_EXPORT ElementList : public QListWidget
{
    Q_OBJECT
public:
    explicit ElementList(QWidget *parent = nullptr);
    ~ElementList();
    /**
     * @brief Set radius of child widgets
     * @param r
     */
    void setRadius(int r);
    /**
     * @brief Add an element to the list
     * @param e
     */
    void addElement(Element *e);
    /**
     * @brief This func is here in the case you want to change the radius of an Element as it is private member.
     * @param e
     * @param r
     */
    static void setRadiusOnElement(Element *e, int *r);
protected:
    void startDrag(Qt::DropActions supportedActions);
private:
    int *m_radius = new int(5);
};

LDA_END_NAMESPACE

#endif // ELEMENTLIST_H
