#include "tasksview.h"

#include <iostream>

#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>

#include <DNotifySender>

#include <QApt/Transaction>

#include <DebconfKDE/DebconfGui.h>
#include <KF5/KIOCore/KProtocolManager>
#include <KF5/KIOCore/kiocore_export.h>

#include "ext/libda-release/daddonsplittedbar.h"

#include "commontools/commonstorage.h"
#include "mainwindow.h"

TransactionModel::TransactionModel(QObject *parent) : QStandardItemModel(0, 5, parent)
{
    setHeaderData(0, Qt::Horizontal, "Type", Qt::ItemDataRole::DisplayRole); //Install, uninstall, upgrade...
    setHeaderData(1, Qt::Horizontal, "State", Qt::ItemDataRole::EditRole); //Downloading, running DPKG...
    setHeaderData(2, Qt::Horizontal, "Error", Qt::ItemDataRole::EditRole); //If an error occurs, show its code
    setHeaderData(3, Qt::Horizontal, "Progress", Qt::ItemDataRole::EditRole); //Percentage
    setHeaderData(4, Qt::Horizontal, "Actions", Qt::ItemDataRole::EditRole); //Pause, resume, cancel...
}

void TransactionModel::reset()
{
    beginResetModel();
    endResetModel();
}

TasksView::TasksView(QWidget *parent) : QTreeView(parent)
{
    //Generates models
    m_model = new TransactionModel(this);
    m_proxyModel = new QSortFilterProxyModel(this);
    m_proxyModel->setSourceModel(m_model);
    setModel(m_proxyModel);

    //Loads UI
    setRootIsDecorated(false);
    setAlternatingRowColors(true);
    setModel(m_model);
    setSortingEnabled(true);
    sortByColumn(2, Qt::AscendingOrder);
    setEditTriggers(QTreeView::EditTrigger::NoEditTriggers);

    QRegExp regExp("", Qt::CaseInsensitive);
    m_proxyModel->setFilterRegExp(regExp);
}

TasksView::~TasksView()
{
    m_model->~TransactionModel();
    m_proxyModel->~QSortFilterProxyModel();
}

void TasksView::load(QString)
{
    wmgr->fillTop(false);
    wmgr->fillBottom(false);
    wmgr->blurTop(false);
    storage->currentWindow->resize(storage->currentWindow->size());//Fix
}

void TasksView::reload() {
    m_model->reset();
}

void TasksView::setData(TransactionModel *model)
{
    m_model = model;
    m_proxyModel->setSourceModel(model);
}

void TasksView::addTransaction(QApt::Transaction *trans, QString type)
{
    std::cout << __func__ << " started." << std::endl;
    m_model->insertRow(m_model->rowCount());

    m_model->setData(m_model->index(m_model->rowCount() -1, 0), type);
    m_model->setData(m_model->index(m_model->rowCount() -1, 1), trans->status());
    m_model->setData(m_model->index(m_model->rowCount() -1, 2), "");
    m_model->setData(m_model->index(m_model->rowCount() -1, 3), QString::number(trans->progress()) + "%");

    int __ROW = m_model->rowCount() -1;

    std::cout << __ROW << " is it null: " << m_model->item(m_model->rowCount() -1, 1) << std::endl;

    connect(trans, &QApt::Transaction::statusChanged, trans, [__ROW, trans, this]() {
        m_model->setData(m_model->index(__ROW, 1), trans->status());
    });
    connect(trans, &QApt::Transaction::finished, trans, [__ROW, trans, this] () {
        m_model->setData(m_model->index(__ROW, 2), "Finished: " + QString::number(trans->exitStatus()));
    });
    connect(trans, &QApt::Transaction::errorOccurred, trans, [__ROW, trans, this]() {
        m_model->setData(m_model->index(__ROW, 2), "ERROR " + QString::number(trans->error()));
    });
    connect(trans, &QApt::Transaction::progressChanged, trans, [__ROW, trans, this]() {
        m_model->setData(m_model->index(__ROW, 3), QString::number(trans->progress()) + "%");
    });

    std::cout << __func__ << " ended." << std::endl;
}

TransactionModel *TasksView::model() const { return m_model; }
QSortFilterProxyModel *TasksView::proxyModel() const { return m_proxyModel; }

TasksManager::TasksManager(QObject *parent) : QObject(parent)
{
    m_view = new TasksView;
    index = 0;
}

TasksManager::~TasksManager()
{
    m_view->~TasksView();
}

void TasksManager::addTransaction(QApt::Transaction *transac, QString type)
{
    std::cout << __func__ << " started." << std::endl;
    if (transac != nullptr) {
        m_view->addTransaction(transac, type);
        data << transac;
        if (!lastEnded) { //Need to run the task
            switchTask();
            std::cout << __func__ << " launched task." << std::endl;
        }
        std::cout << __func__ << " ended to add task." << std::endl;
    }
    std::cout << __func__ << " ended." << std::endl;
}

using Sender = Dtk::Core::DUtil::DNotifySender;

void TasksManager::switchTask() //triggered when another task ended
{
    std::cout << __func__ << " started." << std::endl;
    if (index != data.length()) {
        //Disconnect old, connect new one!
        if (index != 0) { //Cannot get an older task than the first
        }
        runTask(data.at(index));
        index++;
    } else {
        lastEnded = true;
    }
    std::cout << __func__ << " ended." << std::endl;
}

void TasksManager::runTask(QApt::Transaction *trans)
{
    std::cout << __func__ << " started." << std::endl;
    if (!trans->isCancelled()) { //In the case we cancel before we run it!
        if (KProtocolManager::proxyType() == KProtocolManager::ManualProxy) {
            trans->setProxy(KProtocolManager::proxyFor("http"));
        }
        trans->setLocale(QLatin1String(setlocale(LC_MESSAGES, nullptr)));
        trans->run();

        //Tells a task failed
        connect(trans, &QApt::Transaction::errorOccurred, this, [this] (QApt::ErrorCode code) {
            Sender send("Task ended");
            send.timeOut(3000);
            send.appIcon("tienda-deepines");
            send.appName(tr("Tienda Deepines"));
            send.appBody(m_view->model()->data(m_view->model()->index(index-1, 0)).toString() + tr(": failed, code ") + code);
            send.call();
            send.~DNotifySender();
        });
        //Tells a task ended
        connect(trans, &QApt::Transaction::finished, this, [this, trans](QApt::ExitStatus status) {

            QString text = "";
            switch (status) {//Dont' notify for cancel, if someone cancel many tasks, we'll get a lot of notifs. For failePrevious, we don't care, it's previous!
                case QApt::ExitStatus::ExitFailed: text = (m_view->model()->data(m_view->model()->index(index-1, 0)).toString()
                                                          + tr(" failed: ")
                                                          + trans->errorString()); break;
                case QApt::ExitStatus::ExitUnfinished: text = (tr("Looks like something went wrong, the task \"")
                                                               + m_view->model()->data(m_view->model()->index(index-1, 0)).toString()
                                                               + tr("\", it did not finished.")); break;
                case QApt::ExitStatus::ExitSuccess: text = (m_view->model()->data(m_view->model()->index(index-1, 0)).toString()
                                                            + tr(", successfully done.")); break;
                default: break;
            }

            if (!text.isEmpty()) {
                Sender send("Task ended");
                send.timeOut(3000);
                send.appIcon("tienda-deepines");
                send.appName(tr("Tienda Deepines"));
                send.appBody(text);
                send.call();
                send.~DNotifySender();
            }
            switchTask();
        });
    } else {
        switchTask();
    }
    std::cout << __func__ << " ended." << std::endl;
}

AbstractHistoryHandler *TasksManager::view() {return m_view;}
int TasksManager::pendingTasks() {return data.length() - index;}
QApt::Transaction *TasksManager::currentTransaction() {return data.at(index);}
int TasksManager::currentIndex() {return index;}
