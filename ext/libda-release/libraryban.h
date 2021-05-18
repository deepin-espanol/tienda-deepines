#ifndef LIBRARYBAN_H
#define LIBRARYBAN_H

#include "class_decl.h"
#include "libda_global.h"

#include <QApplication>
#include <QLibrary>

class QProcess;

LDA_BEGIN_NAMESPACE

class AbstractPlugin;

/**
 * @brief Abstract layer for a LibraryBan-compliant plugin.
 */
class LIBDA_SHARED_EXPORT AbstractPlugin {
public:
    explicit AbstractPlugin(QObject *p = nullptr);
    virtual ~AbstractPlugin();

    QString version();
    QString author();
    QString release();
    QString website();
    QString description();
    /**
     * @brief Target application name (e.g.: dde-file-manager)
     * @return
     */
    QString target();

protected:
    const QString m_version = "0.0.0.1";
    const QString m_author = "latin";
    const QString m_release = "Test 1";
    const QString m_website = "github.com/deepin-espagnol";
    const QString m_description = "Base plugin";
    const QString m_target = QApplication::applicationName();
};

/**
 * @brief The LibraryBan class is used to filter dynamically linked libraries
 */
class LibraryBan : public QLibrary
{
    Q_OBJECT
public:
    explicit LibraryBan(QObject *parent = nullptr);
    ~LibraryBan();
    /**
     * @brief Says if a library is using one of the libs in libsToBan
     * @return
     */
    inline bool mustBeBan() { return m_ban; }
    /**
     * @brief Libraries that you get notified when checking
     */
    QStringList libsToBan;
    /**
     * @brief Loads a plugin from the lib
     * @return AbstractPlugin you can bind to your own
     */
    AbstractPlugin *loadPlugin();
signals:
    /**
     * @brief Emitted when a lib of libsToBan is detected
     */
    void checkFailed();

public slots:
    void parseOutput();
    void checkLib();

private:
    QProcess *proc;
    bool m_ban = false;
};

LDA_END_NAMESPACE

#endif // LIBRARYBAN_H
