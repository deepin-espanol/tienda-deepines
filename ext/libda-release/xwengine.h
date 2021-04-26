#ifndef XWENGINE_H
#define XWENGINE_H

#include "class_decl.h"
#include "libda_global.h"

#include "abstractelement.h"
#include "translationengine.h"

#include <QWidget>
#include <QList>
#include <QDomDocument>

LDA_BEGIN_NAMESPACE

class LIBDA_SHARED_EXPORT XWEngine : public QObject
{
    Q_OBJECT
public:
    explicit XWEngine(QObject *parent = nullptr);
    QMap<QString, AbstractElement *> elements;

    void loadXML(QString data);
    virtual void generateTree(AbstractElement *p, QDomNode e);
    virtual AbstractElement *generateInstance(QString elementType, QString args);
    virtual AbstractElement *rootElement();
    virtual bool generateConnection(QMap<QString, QVariant> propertiesMatched);

protected:
    bool isFirstValidInstanciation = true;
    bool needsTranslations = false;
    AbstractElement *m_root = nullptr;
    TranslationEngine tsEngine;
};

LDA_END_NAMESPACE

#endif // XWENGINE_H
