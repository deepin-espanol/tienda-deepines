#ifndef IRH_H
#define IRH_H

#include <QObject>
#include <DSingleton>

/**
 * @brief The External Requests Handler, API to make calls to internal funcs
 *        Like showing a PKG (Mainly), use in XWE!
 */
class ERH : public QObject, public Dtk::Core::DSingleton<ERH>
{
    Q_OBJECT
public:
    explicit ERH(QObject *parent = nullptr);

    template <typename Func> void bridge(const typename QtPrivate::FunctionPointer<Func>::Object *src, Func sig);
    Q_SLOT void generatePkgRequest(QString n);
};

#endif // IRH_H
