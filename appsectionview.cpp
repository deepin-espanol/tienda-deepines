#include "appsectionview.h"

#include "commontools/commonstorage.h"

AppSectionView::AppSectionView(QWidget *parent) : QTreeView(parent)
{
    filter = new ProxyDataModel(this);
    filter->setSourceModel(&CommonStorage::instance()->model);
}

AppSectionView::~AppSectionView()
{
    filter->~ProxyDataModel();
    this->QTreeView::~QTreeView();
}

void AppSectionView::setSection(QString section)
{
    filter->setSectionFiltered(section);
}
