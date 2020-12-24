#ifndef SORTMODEL_H
#define SORTMODEL_H

#include <QDate>
#include <QSortFilterProxyModel>

enum PFSState {
    None, //Means any
    Update,
    Installed,
    NotInstalled
};

struct PackagesFilterScheme {
    /**
      * @brief includes the input or have to be equal
      */
    bool inUse = false;
    bool includedString = true;
    QString name = ""; //Empty means any
    QString version = ""; //Empty means any
    QString arch = ""; //Empty means any
    QString section = ""; //Empty means any
    PFSState state = PFSState::None;
};

class FilterOptionsWidget;

class SortFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit SortFilterModel(QWidget *p = nullptr);
    SortFilterModel(FilterOptionsWidget *parent);
    PackagesFilterScheme scheme();

public Q_SLOTS:
    void setScheme(PackagesFilterScheme scheme);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

private:
    PackagesFilterScheme m_scheme;
};

#endif // SORTMODEL_H
