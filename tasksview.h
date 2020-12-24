#ifndef TASKSVIEW_H
#define TASKSVIEW_H

#include "sortmodel.h"
#include "abstracthistoryhandler.h"

#include <QStandardItemModel>
#include <QTreeView>
#include <QFile>
#include <qapt/transaction.h>
#include <DGuiApplicationHelper>

class TransactionModel : public QStandardItemModel
{
    Q_OBJECT
public:
    explicit TransactionModel(QObject *parent = nullptr);

public Q_SLOTS:
    void reset();
};

class TasksView : public QTreeView, AbstractHistoryHandler
{
    Q_OBJECT
public:
    explicit TasksView(QWidget *parent = nullptr);
    ~TasksView();
    TransactionModel *model() const;
    QSortFilterProxyModel *proxyModel() const;
    inline virtual QWidget *self() const override {return (QWidget*)(this);}
    inline virtual void load(QString) override {}

public Q_SLOTS:
    void reload();
    void setData(TransactionModel *model);
    void addTransaction(QApt::Transaction *transac, QString type);

private:
    TransactionModel *m_model = nullptr;
    QSortFilterProxyModel *m_proxyModel = nullptr;
};

class TasksManager : QObject
{
    Q_OBJECT
public:
    explicit TasksManager(QObject *parent = nullptr);
    ~TasksManager();

    inline static TasksManager *instance() {
        static TasksManager *inst = new TasksManager;
        return inst;
    }

    QWidget *view();
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
