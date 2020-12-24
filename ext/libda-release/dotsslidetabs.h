#ifndef DOTSSLIDETABS_H
#define DOTSSLIDETABS_H

#include "libda_global.h"
#include <QWidget>

class QStackedWidget;

LDA_BEGIN_NAMESPACE

class LIBDA_SHARED_EXPORT DotsSlideTabs : public QWidget
{
    Q_OBJECT
public:
    DotsSlideTabs(QStackedWidget *source, int dots = 5, QWidget *parent = nullptr);
    DotsSlideTabs(QStackedWidget *source, QWidget *parent = nullptr);

public Q_SLOTS:
    void setSource(QStackedWidget *source);
    void setMaximumVisibleDots(int dots);
    void setDotsSize(int size);
    void enableAutoDotsSizeUpdate(bool enable = true);

private Q_SLOTS:
    void updateStates();

protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void resizeEvent(QResizeEvent *e) override;
    void paintEvent(QPaintEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void enterEvent(QEvent *e) override;
    void leaveEvent(QEvent *e) override;
    bool event(QEvent *e) override;
    virtual void updateDotsSize();

private:
    void raiseConnections();
    void closeConnections();

    QStackedWidget *m_source = nullptr;
    int max_dots;
    int m_visibleDots = 0;
    int m_currentDot = 0;
    int m_dotSize = 0;
    int hoveredDot = -1;
    bool clicked = false;
    bool hovered = false;
    bool m_enableAutoUpdates = true;
};

LDA_END_NAMESPACE

#endif // DOTSSLIDETABS_H
