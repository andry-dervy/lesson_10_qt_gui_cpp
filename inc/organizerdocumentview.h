#ifndef ORGANIZERDOCUMENTVIEW_H
#define ORGANIZERDOCUMENTVIEW_H

#include "documentview.h"
#include "QQuickWidget"
#include <QDateTime>
#include <QAbstractListModel>
#include <QQuickView>

class Task: public QObject
{
    Q_OBJECT

public:
    Task(QObject* obj = nullptr);
    Task(QString&& aName, QString&& aDescription, int aProgress, QDate&& aLimitDate,  QObject* obj = nullptr);
    virtual ~Task(){}
    void setName(QString& aName){name = aName;}
    void setDescription(QString& aDescription){description = aDescription;}
    void setProgress(int aProgress){
        progress = aProgress > 10 || aProgress < 0 ? 0: aProgress;}
    void setLimitDate(QDate& aLimitDate) {
        limitDate = aLimitDate;}

    QString getName(){return name;}
    QString getDescription(){return description;}
    int getProgress(){return progress;}
    QDate getLimitDate(){return limitDate;}

private:
    QString name;
    QString description;
    int progress;
    QDate limitDate;

public:
    static const int MinProgress = 0;
    static const int MaxProgress = 10;
};

class TasksListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        NameRole = Qt::UserRole + 1,
        DescriptionRole,
        ProgressRole,
        LimitDateRole
    };

    TasksListModel(QObject *parent = nullptr);
    ~TasksListModel() override {}

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void add();
    Q_INVOKABLE void remove(int index);
    Q_INVOKABLE void update_name_task(int index, QString aName);
    Q_INVOKABLE void update_description_task(int index, QString aDescription);
    Q_INVOKABLE void update_progress_task(int index, int update);
    Q_INVOKABLE void update_limit_date(int index, int update);

    void add(Task* task);
    const QList<Task*>& getListTask() const {return tasks;}

private:
    QList<Task*> tasks;

private:
    inline bool indexIsNotValid(int index) {return index < 0 || index >= tasks.size();}
};

class OrganizerDocumentView : public DocumentView
{
    Q_OBJECT

public:
    OrganizerDocumentView(QWidget* parent);
    ~OrganizerDocumentView() override = default;
    bool openDocument(QFile& file, ReadableWritable rw) override;
    bool saveDocument(QFile& file) override;
    void print(QPrinter* printer) const override;
    bool isTypeDoc(TypeDocumentView type) const override;
    QString getExtention() const override {return extention();}
    static QString extention() {return "xmlorg";}
private:
    OrganizerDocumentView& operator=(const OrganizerDocumentView&) = delete;
    OrganizerDocumentView(OrganizerDocumentView&& root) = delete;
    OrganizerDocumentView& operator=(OrganizerDocumentView&&) = delete;

private:
    QQuickWidget* quickWidget;
    TasksListModel* model;
    QQuickView* view;

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
};

class CreatorOrganizerDocumentView: public CreatorDocumentView
{
public:
    CreatorOrganizerDocumentView(QObject* parent)
        :CreatorDocumentView(parent) {}
    ~CreatorOrganizerDocumentView() override {}
    DocumentView* newDocumentView(QWidget* parent = nullptr) override;
    DocumentView* openDocumentView(QString& fileName, QWidget* parent = nullptr, ReadableWritable rw = ReadableWritable::WRITABLE) override;
    bool saveDocumentView(QString& fileName, DocumentView& docView) override;
protected:
    virtual void fun() override;
};

#endif // ORGANIZERDOCUMENTVIEW_H
