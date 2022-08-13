#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include "inc/organizerdocumentview.h"

class TestTasksListModel : public QObject
{
    Q_OBJECT

    TasksListModel* model;
    Task* t;

    QString name;
    QString desc;
    int prog;
    QDate date;

public:
    TestTasksListModel();
    ~TestTasksListModel();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void test_rowCount();
    void test_data();
    void test_roleNames();
    void test_getListTask();

};

TestTasksListModel::TestTasksListModel()
{

}

TestTasksListModel::~TestTasksListModel()
{

}

void TestTasksListModel::initTestCase()
{
    model = new TasksListModel();

    t = new Task();
}

void TestTasksListModel::cleanupTestCase()
{
    delete t;
    delete  model;
}

void TestTasksListModel::init()
{
    name = "Name";
    desc = "Description";
    prog = 5;
    date = QDate::currentDate();

    t->setName(name);
    t->setDescription(desc);
    t->setProgress(prog);
    t->setLimitDate(date);
}

void TestTasksListModel::test_rowCount()
{
    const QModelIndex indx{model->index(0)};
    QVERIFY(model->rowCount(indx) == 0);
    model->add();
    QVERIFY(model->rowCount(indx) == 1);
    model->add();
    QVERIFY(model->rowCount(indx) == 2);
    model->remove(-1);
    QVERIFY(model->rowCount(indx) == 2);
    model->remove(model->rowCount(indx)+1);
    QVERIFY(model->rowCount(indx) == 2);
    model->remove(model->rowCount(indx)-1);
    QVERIFY(model->rowCount(indx) == 1);
    model->remove(0);
    QVERIFY(model->rowCount(indx) == 0);
}

void TestTasksListModel::test_data()
{
    model->add(t);

    const QModelIndex indx{model->index(0)};
    QVERIFY(model->data(indx,TasksListModel::Roles::NameRole).toString() == name);
    name = "NewName";
    model->update_name_task(-1,name);
    QVERIFY(model->data(indx,TasksListModel::Roles::NameRole).toString() != name);
    model->update_name_task(10,name);
    QVERIFY(model->data(indx,TasksListModel::Roles::NameRole).toString() != name);
    model->update_name_task(0,name);
    QVERIFY(model->data(indx,TasksListModel::Roles::NameRole).toString() == name);

    QVERIFY(model->data(indx,TasksListModel::Roles::DescriptionRole).toString() == desc);
    desc = "NewDescription";
    model->update_description_task(-1,desc);
    QVERIFY(model->data(indx,TasksListModel::Roles::DescriptionRole).toString() != desc);
    model->update_description_task(2,desc);
    QVERIFY(model->data(indx,TasksListModel::Roles::DescriptionRole).toString() != desc);
    model->update_description_task(0,desc);
    QVERIFY(model->data(indx,TasksListModel::Roles::DescriptionRole).toString() == desc);

    QVERIFY(model->data(indx,TasksListModel::Roles::ProgressRole).toInt() == prog);
    model->update_progress_task(0,-1);
    QVERIFY(model->data(indx,TasksListModel::Roles::ProgressRole).toInt() != prog-1);
    model->update_progress_task(0,1);
    QVERIFY(model->data(indx,TasksListModel::Roles::ProgressRole).toInt() == prog);
    model->update_progress_task(0,0);
    QVERIFY(model->data(indx,TasksListModel::Roles::ProgressRole).toInt() == prog);

    QVERIFY(model->data(indx,TasksListModel::Roles::NameRole).toDate() == date);
    model->update_limit_date(0,-1);
    QVERIFY(model->data(indx,TasksListModel::Roles::NameRole).toDate() == date.addDays(-1));
    model->update_limit_date(0,1);
    QVERIFY(model->data(indx,TasksListModel::Roles::NameRole).toDate() == date);
    model->update_limit_date(0,0);
    QVERIFY(model->data(indx,TasksListModel::Roles::NameRole).toDate() == date);

    model->remove(0);
    QVERIFY(model->rowCount(indx) == 0);
}

void TestTasksListModel::test_roleNames()
{
    auto roles = model->roleNames();
    QVERIFY(roles[TasksListModel::Roles::NameRole] == "name");
    QVERIFY(roles[TasksListModel::Roles::DescriptionRole] == "description");
    QVERIFY(roles[TasksListModel::Roles::ProgressRole] == "progress");
    QVERIFY(roles[TasksListModel::Roles::LimitDateRole] == "limitDate");
}

void TestTasksListModel::test_getListTask()
{
    model->add(t);
    model->add(t);
    model->add(t);

    auto list = model->getListTask();
    QVERIFY(list.size() == 3);

    model->remove(0);
    model->remove(0);
    model->remove(0);

    list = model->getListTask();
    QVERIFY(list.size() == 0);
}

QTEST_MAIN(TestTasksListModel)

#include "tst_taskslistmodel.moc"
