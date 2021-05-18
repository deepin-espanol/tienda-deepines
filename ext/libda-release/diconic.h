#ifndef DICONLOOKUP_H
#define DICONLOOKUP_H

#include "libda_global.h"
#include <QObject>

LDA_BEGIN_NAMESPACE

/**
 * @brief Provides icon lookup of libdtk available images/icons
 */
class LIBDA_SHARED_EXPORT DIconic : public QObject
{
    Q_OBJECT
public:
    explicit DIconic(QObject *parent = nullptr);
    ~DIconic();

    /**
     * @brief The IconScopes enum, scope used to perform lookups
     * @return Sections you want the lookup be performed in
     */
    enum IconScopes {
        All,
        BuiltIn,
        BuiltInIcon,
        Assets,
        Light,
        Dark,
        BuiltInText,
        Chameleon
    };

    /**
     * @brief Make an icon lookup in the available paths depending of the scope. Not found gives an icon too.
     * @param icon_name
     * @param scope
     * @return QIcon* with the icon or or banned icon if not found.
     */
    // The result can depend of the versions, better is to use IconScope::All (cross version)
    static QIcon *fromString(const QString icon_name, IconScopes scope = IconScopes::All);

    /**
     * @brief A list of available icons (and their paths)
     * @return QStringList of FPs
     */
    static QStringList list();

    /**
     * @brief A list of path that are available to search an icon
     * @return QStringList of dirs for lookups
     */
    static QStringList listPaths();
};

LDA_END_NAMESPACE

#endif // DICONLOOKUP_H
