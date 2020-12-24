#ifndef TRANSLATIONENGINE_H
#define TRANSLATIONENGINE_H

#include "class_decl.h"
#include "libda_global.h"

#include <QObject>
#include <QMap>

LDA_BEGIN_NAMESPACE

class LIBDA_SHARED_EXPORT TranslationEngine : public QObject
{
    Q_OBJECT
public:
    explicit TranslationEngine(QObject *parent = nullptr);
    bool loadXMLFallback(QString fbk);
    bool loadXMLMain(QString main);
    QString translate(QString source);

private:
    QMap<QString, QString> m_fbk;
    QMap<QString, QString> m_main;
};

LDA_END_NAMESPACE

#endif // TRANSLATIONENGINE_H
