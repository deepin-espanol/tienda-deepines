#ifndef ELEMENT_H
#define ELEMENT_H

#include "libda_global.h"
#include <QFrame>

LDA_BEGIN_NAMESPACE
class ProxyPainter;

/**
 * @brief The Element class is a wrapper in the case you want a UI plugin system with restrictions
 */
class LIBDA_SHARED_EXPORT Element : public QFrame {
public:
    Element(int height = 10, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    virtual ~Element() override;
    //Classic paint event handler that will then send it to Element::paint(...) to ensure painting will never cause issue
    void paintEvent(QPaintEvent *e) override;
    /**
     * @brief sizeHint
     * @return The size hint for the widget, changed to have something good in any case
     */
    QSize sizeHint() const override;
    /**
     * @brief Radius for the corners when using
     * @return
     */
    int radius();
protected:
    //To make the widgets unable to have an unauthorized size
    void resizeEvent(QResizeEvent *e) override;
    //To ensure paintings will don't cause issue
    /**
     * @brief To make the Element's painting you MUST reimplement this function!
     * @param painter
     * @param event
     */
    virtual void paint(ProxyPainter *painter, const QPaintEvent *event);

    //For DnD impl.
    void dropEvent(QDropEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragLeaveEvent (QDragLeaveEvent *event) override;
private:
    int *rad = new int(5);
    int m_height = 10;
    friend class ElementList;
};

/**
 * @brief An implementation to try the Element class and see what it can do
 */
class LIBDA_SHARED_EXPORT DerivedElement : public Element
{
public:
    explicit DerivedElement(int s = 10);
    ~DerivedElement() override;
    void paint(ProxyPainter *painter, const QPaintEvent *event) override;
};

LDA_END_NAMESPACE

#endif // ELEMENT_H
