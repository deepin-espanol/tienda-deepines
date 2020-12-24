#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include <DSearchEdit>

DWIDGET_USE_NAMESPACE

class SearchBar : public DSearchEdit
{
    Q_OBJECT
public:
    explicit SearchBar(QWidget *p);
    ~SearchBar();
};

#endif // SEARCHBAR_H
