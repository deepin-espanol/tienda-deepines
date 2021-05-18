#ifndef LAYOUTS_H
#define LAYOUTS_H

#include "ext/libda-release/basicelements.h"

class HLayout : public Dtk::Addons::HBoxLayout
{
    Q_OBJECT
    Q_PROPERTY(int leftMargin WRITE setLeftMargin READ leftMargin)
    Q_PROPERTY(int rightMargin WRITE setRightMargin READ rightMargin)
    Q_PROPERTY(int bottomMargin WRITE setBottomMargin READ bottomMargin)
    Q_PROPERTY(int topMargin WRITE setTopMargin READ topMargin)
public:
    explicit HLayout(QWidget *p = nullptr);
    virtual QObject *self() override;
    virtual void addElement(AbstractElement *e) override;

    int leftMargin();
    int rightMargin();
    int topMargin();
    int bottomMargin();

/*public QT_ANNOTATE_ACCESS_SPECIFIER(qt_signal):
    void leftMarginChanged(int v);
    void rightMarginChanged(int v);
    void topMarginChanged(int v);
    void bottomMarginChanged(int v);*/

public Q_SLOTS:
    void setLeftMargin(int v);
    void setRightMargin(int v);
    void setTopMargin(int v);
    void setBottomMargin(int v);
};

class VLayout : public Dtk::Addons::VBoxLayout
{
    Q_OBJECT
    Q_PROPERTY(int leftMargin WRITE setLeftMargin READ leftMargin)
    Q_PROPERTY(int rightMargin WRITE setRightMargin READ rightMargin)
    Q_PROPERTY(int bottomMargin WRITE setBottomMargin READ bottomMargin)
    Q_PROPERTY(int topMargin WRITE setTopMargin READ topMargin)
public:
    explicit VLayout(QWidget *p = nullptr);
    virtual QObject *self() override;
    virtual void addElement(AbstractElement *e) override;

    int leftMargin();
    int rightMargin();
    int topMargin();
    int bottomMargin();

/*Q_SIGNALS:
    void leftMarginChanged(int v);
    void rightMarginChanged(int v);
    void topMarginChanged(int v);
    void bottomMarginChanged(int v);*/

public Q_SLOTS:
    void setLeftMargin(int v);
    void setRightMargin(int v);
    void setTopMargin(int v);
    void setBottomMargin(int v);
};

#endif // LAYOUTS_H
