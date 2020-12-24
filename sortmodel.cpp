#include "sortmodel.h"

#include "filteroptionswidget.h"
#include <iostream>

SortFilterModel::SortFilterModel(QWidget *p) : QSortFilterProxyModel(p) {}
SortFilterModel::SortFilterModel(FilterOptionsWidget *parent) : QSortFilterProxyModel(parent)
{
    connect(parent, &FilterOptionsWidget::schemeUpdated, this, &SortFilterModel::setScheme);
}

PackagesFilterScheme SortFilterModel::scheme() { return m_scheme; }
void SortFilterModel::setScheme(PackagesFilterScheme scheme)
{
    m_scheme = scheme;
    invalidateFilter();
}

bool SortFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QString name = sourceModel()->data(sourceModel()->index(sourceRow, 0, sourceParent)).toString();
    QString vers = sourceModel()->data(sourceModel()->index(sourceRow, 1, sourceParent)).toString();
    QString cvers = sourceModel()->data(sourceModel()->index(sourceRow, 2, sourceParent)).toString();
    QString arch = sourceModel()->data(sourceModel()->index(sourceRow, 3, sourceParent)).toString();
    QString sect = sourceModel()->data(sourceModel()->index(sourceRow, 4, sourceParent)).toString();
    QString state = sourceModel()->data(sourceModel()->index(sourceRow, 5, sourceParent)).toString();

    bool includes = true;

    if (m_scheme.inUse == false) {
        if (m_scheme.name.isEmpty() != true) {
            if (m_scheme.includedString) {
                if (!name.contains(m_scheme.name)) {
                    includes = false;
                }
            } else {
                if (m_scheme.includedString != name) {
                    includes = false;
                }
            }
        }
        if (m_scheme.version.contains(vers) != true && m_scheme.version.contains(cvers) != true && m_scheme.version.isEmpty() != true) {
            includes = false;
        }
        if (m_scheme.section.contains(sect) != true && m_scheme.section.isEmpty() != true) {
            includes = false;
        }
        if (m_scheme.state != PFSState::None) {
            includes = false;
        }
    }

    return includes;
}


static bool isVariantLessThan(const QVariant &left, const QVariant &right,
                                                  Qt::CaseSensitivity cs, bool isLocaleAware)
{
    if (left.userType() == QMetaType::UnknownType)
        return false;
    if (right.userType() == QMetaType::UnknownType)
        return true;
    switch (left.userType()) {
    case QMetaType::Int:
        return left.toInt() < right.toInt();
    case QMetaType::UInt:
        return left.toUInt() < right.toUInt();
    case QMetaType::LongLong:
        return left.toLongLong() < right.toLongLong();
    case QMetaType::ULongLong:
        return left.toULongLong() < right.toULongLong();
    case QMetaType::Float:
        return left.toFloat() < right.toFloat();
    case QMetaType::Double:
        return left.toDouble() < right.toDouble();
    case QMetaType::QChar:
        return left.toChar() < right.toChar();
    case QMetaType::QDate:
        return left.toDate() < right.toDate();
    case QMetaType::QTime:
        return left.toTime() < right.toTime();
    case QMetaType::QDateTime:
        return left.toDateTime() < right.toDateTime();
    case QMetaType::QString:
    default:
        if (isLocaleAware)
            return left.toString().localeAwareCompare(right.toString()) < 0;
        else
            return left.toString().compare(right.toString(), cs) < 0;
    }
}

bool SortFilterModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    QVariant l = (source_left.model() ? source_left.model()->data(source_left, filterRole()) : QVariant());
    QVariant r = (source_right.model() ? source_right.model()->data(source_right, filterRole()) : QVariant());
    return isVariantLessThan(l, r, sortCaseSensitivity(), isSortLocaleAware());
}
