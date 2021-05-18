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

/**
 * @brief XWE is an XML interpretation that relies on in-app instanciation to control exposed elements.
 */
class LIBDA_SHARED_EXPORT XWEngine : public QObject
{
    Q_OBJECT
public:
    explicit XWEngine(QObject *parent = nullptr);

    /**
     * @brief Load XML data end interpret it.
     * @param data
     * @return Returns if the load failed (false) or succeed.
     */
    bool loadXML(QString data);
    /**
     * @brief Process XML data and sets up the target instance that is passed in.
     * @param p The parent node
     * @param e The XML data
     * @return A new
     */
    virtual AbstractElement *instanceSetup(AbstractElement *p, QDomNode e);
    /**
     * @brief Recursive function used to link P2C nodes and object instances.
     * @param p The sinner
     * @param e The XML node content
     */
    virtual void generateTree(AbstractElement *p, QDomNode e);
    /**
     * @brief Generate objects' instances
     * @param elementType
     * @param args
     * @return void
     */
    virtual AbstractElement *generateInstance(QString elementType, QString args);
    /**
     * @brief Get the root element, first QObject-valid element found, from beginning (if found).
     * @return The root, top element
     */
    virtual AbstractElement *rootElement();
    /**
     * @brief Process `connect` node, used for custom signal/slot connection between instances.
     * @param propertiesMatched
     * @return
     */
    virtual bool generateConnection(QMap<QString, QVariant> &propertiesMatched);

    /**
     * @brief Behaviour is to print console messages about what is happening.
     */
    bool enableDebug = false;
    /**
     * @brief If during the parsing, we have to process app's events.
     */
    bool enableAppEvents = true;
    /**
     * @brief Enable auto-parenting. If no parent is specified, automatically attach to parent instance (parent node).
     */
    bool enableAutoParenting = true;
    /**
     * @brief Enable QObject-parenting, not related to node parenting.
     */
    bool enableObjectParenting = true;

    /**
     * @brief (XML) Content that have been loaded to generate object instances.
     * @return QString
     */
    QString getSourceContent();

    /**
     * @brief Get total nuber of objects created by parsing (nullptr are excluded of counting).
     * @return
     */
    int objectCount();

protected:
    /**
     * @brief Debug outputs level of indentation.
     */
    int currentIndent = 0;
    /**
     * @brief Currently in-use XML DOM.
     */
    QDomDocument doc;
    /**
     * @brief Translation engine
     */
    TranslationEngine tsEngine;
    /**
     * @brief Root element of the XML DOM.
     */
    AbstractElement *m_root = nullptr;
    /**
     * @brief Mapped elements by IDs.
     */
    QMap<QString, AbstractElement *> elements;
    /**
     * @brief Used to know if it is the first QObject-valid instance, if yes, set the root.
     */
    bool isFirstValidInstanciation = true;
    /**
     * @brief Used while setting up the properties, translate a text, so the values.
     */
    bool needsTranslations = false;
    /**
     * @brief Object creation count.
     */
    int objC = 0;
};

LDA_END_NAMESPACE

#endif // XWENGINE_H
