#ifndef WIDGETSTACKER_H
#define WIDGETSTACKER_H

#include <QWidget>

class WidgetStacker : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetStacker(QWidget *parent = nullptr);

    Q_SIGNAL void widgetChanged();
    QWidget *currentWidget();
    QList<QWidget *> widgets();

public Q_SLOTS:
    void addWidget(QWidget *);
    void setCurrentWidget(QWidget *w);

protected:
    void paintEvent(QPaintEvent *e);
    bool eventFilter(QObject *src, QEvent *e);
    void resizeEvent(QResizeEvent *e);

private:
    QList<QWidget *> m_widgets;
    QWidget *currWidget = nullptr;
    bool paintCalled = false;
};

#endif // WIDGETSTACKER_H
