#ifndef FILTEROPTIONSWIDGET_H
#define FILTEROPTIONSWIDGET_H

#include "sortmodel.h"
#include <QWidget>

/**
 * @brief Not used yet. To show additional settings for PKG lookups
 */
class FilterOptionsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FilterOptionsWidget(QWidget *parent = nullptr);
    ~FilterOptionsWidget();
    PackagesFilterScheme *scheme();

public: Q_SIGNALS:
    void schemeUpdated(PackagesFilterScheme sch);

private:
    void loadUI();
    PackagesFilterScheme *m_scheme;
};

#endif // FILTEROPTIONSWIDGET_H
