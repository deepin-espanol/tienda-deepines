#ifndef BASICELEMENTS_H
#define BASICELEMENTS_H

#include "class_decl.h"
#include "libda_global.h"
#include "abstractelement.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QLineEdit>

LDA_BEGIN_NAMESPACE

class LIBDA_SHARED_EXPORT Widget : public QWidget, public AbstractElement
{
    Q_OBJECT
public:
    explicit Widget();
    virtual QObject *self() override;
    virtual void addElement(AbstractElement *element) override;
};


class LIBDA_SHARED_EXPORT VBoxLayout : public QVBoxLayout, public AbstractElement
{
    Q_OBJECT
public:
    explicit VBoxLayout();
    virtual QObject *self() override;
    virtual void addElement(AbstractElement *element) override;
};

class LIBDA_SHARED_EXPORT LineEdit : public QLineEdit, public AbstractElement
{
    Q_OBJECT
public:
    explicit LineEdit();
    virtual QObject *self() override;
    virtual void addElement(AbstractElement *element) override;
};

class LIBDA_SHARED_EXPORT Label : public QLabel, public AbstractElement
{
    Q_OBJECT
public:
    explicit Label();
    virtual QObject *self() override;
    virtual void addElement(AbstractElement *element) override;
};

class LIBDA_SHARED_EXPORT HBoxLayout : public QHBoxLayout, public AbstractElement
{
    Q_OBJECT
public:
    explicit HBoxLayout();
    virtual QObject *self() override;
    virtual void addElement(AbstractElement *element) override;
};

LDA_END_NAMESPACE

#endif // BASICELEMENTS_H
