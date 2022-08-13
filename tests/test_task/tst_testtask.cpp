#include <QtTest>
#include <QCoreApplication>

// add necessary includes here
#include <inc/organizerdocumentview.h>

class TestTask : public QObject
{
    Q_OBJECT

public:
    TestTask();
    ~TestTask();

private:
    Task* task;

private slots:
    void initTestCase();
    void cleanupTestCase();

    void test_Constructor();
    void test_setName();
    void test_setDescription();
    void test_setProgress();
    void test_setLimitDate();
};

TestTask::TestTask()
{

}

TestTask::~TestTask()
{

}

void TestTask::initTestCase()
{
    task = new Task;
}

void TestTask::cleanupTestCase()
{
    delete task;
}

void TestTask::test_Constructor()
{
    Task* t = new Task;
    QVERIFY(t->getName() == "Название задачи");
    QVERIFY(t->getDescription() == "Описание задачи");
    QVERIFY(t->getProgress() == 0);
    QVERIFY(t->getLimitDate() == QDate::currentDate());
    delete t;
    t = new Task("Название задачи","Описание задачи",2,QDate::currentDate().addDays(1));
    QVERIFY(t->getName() == "Название задачи");
    QVERIFY(t->getDescription() == "Описание задачи");
    QVERIFY(t->getProgress() == 2);
    QVERIFY(t->getLimitDate() == QDate::currentDate().addDays(1));
    delete t;
}

void TestTask::test_setName()
{
    QString name{"asdf"};
    task->setName(name);
    QVERIFY(task->getName() == name);
}

void TestTask::test_setDescription()
{
    QString desc{"asdf"};
    task->setDescription(desc);
    QVERIFY(task->getDescription() == desc);
}

void TestTask::test_setProgress()
{
    task->setProgress(0);
    QVERIFY(task->getProgress() == 0);
    task->setProgress(10);
    QVERIFY(task->getProgress() == 10);
    task->setProgress(5);
    QVERIFY(task->getProgress() == 5);
    task->setProgress(-1);
    QVERIFY(task->getProgress() == 0);
    task->setProgress(11);
    QVERIFY(task->getProgress() == 0);
}

void TestTask::test_setLimitDate()
{
    QDate date{QDate::currentDate()};
    task->setLimitDate(date);
    QVERIFY(task->getLimitDate() == date);
    date = date.addDays(-2);
    task->setLimitDate(date);
    QVERIFY(task->getLimitDate() == date);
    date = date.addDays(+6);
    task->setLimitDate(date);
    QVERIFY(task->getLimitDate() == date);
}

QTEST_MAIN(TestTask)

#include "tst_testtask.moc"
