#ifndef STATISTICSVIEW_H
#define STATISTICSVIEW_H

#include "statistics/animatorloader.h"
#include "statistics/bigprogressor.h"
#include "statistics/smallprogressor.h"
#include "statistics/flattile.h"

#include "historymanager.h"

#include <QScrollArea>

class FlowLayout;

/**
 * @brief STSV class, used to show statistics provided
 */
class StatisticsView : public QScrollArea, public AbstractHistoryHandler
{
public:
    StatisticsView();
    void addElement(QWidget *w, AnimatorElement *e = nullptr);
    FlatContainer content;
    FlowLayout *contentLayout;

    inline virtual QWidget *widget() const override {return (QWidget*)(this);}
    inline void load(QString) override;

private:
    BigProgressor installedOnes;
    SmallProgressor residualConfOnes;
    SmallProgressor orphanedOnes;
    BigProgressor importantOnes;
    SmallProgressor instPolBrokOnes;
    SmallProgressor nowPolBrokOnes;
    BigProgressor nowBrokOnes;
    SmallProgressor notDownOnes;
    BigProgressor updateOnes;
};

#endif // STATISTICSVIEW_H
