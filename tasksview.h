#ifndef TASKSVIEW_H
#define TASKSVIEW_H

#include "sortmodel.h"
#include "commontools/historymanager.h"

#include <QStandardItemModel>
#include <QTreeView>
#include <QFile>
#include <DGuiApplicationHelper>

namespace QApt {
    class Transaction;
}

/**
 * @brief TSV UI model
 */
class TransactionModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit TransactionModel(QObject *parent = nullptr);

public Q_SLOTS:
    void reset();
};

/**
 * @brief TSV class, shows pending and current transacions
 */
class TasksView : public QTreeView, public AbstractHistoryHandler
{
    Q_OBJECT
public:
    explicit TasksView(QWidget *parent = nullptr);
    ~TasksView();
    TransactionModel *model() const;
    QSortFilterProxyModel *proxyModel() const;
    inline virtual QWidget *widget() const override {return (QWidget*)(this);}
    virtual void load(QString) override;

public Q_SLOTS:
    void reload();
    void setData(TransactionModel *model);
    void addTransaction(QApt::Transaction *transac, QString type);

private:
    TransactionModel *m_model = nullptr;
    QSortFilterProxyModel *m_proxyModel = nullptr;
};

/**
 * @brief TSKMGR is used for APT BKD to handle the order of the tasks and if they cause behaviours not know from user
 */
class TasksManager : public QObject
{
    Q_OBJECT
public:
    explicit TasksManager(QObject *parent = nullptr);
    ~TasksManager();

    inline static TasksManager *instance() {
        static TasksManager *inst = new TasksManager;
        return inst;
    }

    AbstractHistoryHandler *view();
    int pendingTasks();
    QApt::Transaction *currentTransaction();
    int currentIndex();

public Q_SLOTS:
    void addTransaction(QApt::Transaction *transac, QString type);

private:
    QList<QApt::Transaction *> data;
    TasksView *m_view = nullptr;
    int index = 0;
    bool lastEnded = false;

    void switchTask();
    void runTask(QApt::Transaction *trans);
};

#endif // TASKSVIEW_H
