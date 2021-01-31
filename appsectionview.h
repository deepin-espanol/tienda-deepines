#ifndef APPSECTIONVIEW_H
#define APPSECTIONVIEW_H

#include "proxydatamodel.h"
#include <QTreeView>

/**
 * @brief List to show all apps nor pkgs provided
 */
class AppSectionView : public QTreeView
{
    Q_OBJECT
public:
    explicit AppSectionView(QWidget *parent);
    ~AppSectionView();

public Q_SLOTS:
    void setSection(QString section);

private:
    ProxyDataModel *filter;
};

#endif // APPSECTIONVIEW_H
