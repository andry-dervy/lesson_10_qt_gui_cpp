#include "inc/organizerdocumentview.h"
#include <QEvent>
#include "QMdiSubWindow"
#include <QDateTime>
#include <QQmlContext>
#include <QXmlStreamWriter>
#include <QQuickItem>
#include <QDebug>

Task::Task(QObject* obj)
    :QObject(obj)
    ,name(tr("Название задачи"))
    ,description(tr("Описание задачи"))
    ,progress(0)
    ,limitDate(QDate::currentDate())
{}

Task::Task(QString&& aName, QString&& aDescription, int aProgress, QDate&& aLimitDate, QObject* obj)
    :QObject(obj)
    ,name(aName)
    ,description(aDescription)
    ,progress(aProgress)
    ,limitDate(aLimitDate)
{}

TasksListModel::TasksListModel(QObject *parent)
    :QAbstractListModel(parent)
{}

int TasksListModel::rowCount(const QModelIndex &index) const
{
    if (index.isValid()) {
        return 0;
    }
    return  tasks.size();
}

QVariant TasksListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if(index.row() < 0 || index.row() >= tasks.size()) {
        return QVariant();
    }

    switch (role) {
    case NameRole:
        return tasks.at(index.row())->getName();
    case DescriptionRole:
        return tasks.at(index.row())->getDescription();
    case ProgressRole:
        return tasks.at(index.row())->getProgress();
    case LimitDateRole:
        return tasks.at(index.row())->getLimitDate().toString("dd.MM.yyyy");
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> TasksListModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles[Roles::NameRole] = "name";
    roles[Roles::DescriptionRole] = "description";
    roles[Roles::ProgressRole] = "progress";
    roles[Roles::LimitDateRole] = "limitDate";

    return roles;
}

void TasksListModel::add()
{
    auto task = new Task(this);
    if(!task) return;
    beginInsertRows(QModelIndex(), tasks.size(), tasks.size());
    tasks.append(task);
    endInsertRows();
}

void TasksListModel::remove(int index)
{
    if(indexIsNotValid(index)) return;
    beginRemoveRows(QModelIndex(), index, index);
    tasks.removeAt(index);
    endRemoveRows();
}

void TasksListModel::update_name_task(int index, QString aName)
{
    if(indexIsNotValid(index)) return;

    tasks.at(index)->setName(aName);
}

void TasksListModel::update_description_task(int index, QString aDescription)
{
    if(indexIsNotValid(index)) return;

    tasks.at(index)->setDescription(aDescription);
}

void TasksListModel::update_progress_task(int index, int update)
{
    if(indexIsNotValid(index)) return;
    if(update == 0) return;

    auto progress = tasks.at(index)->getProgress();

    if(update > 0 && progress < Task::MaxProgress) ++progress;
    if(update < 0 && progress > Task::MinProgress) --progress;

    tasks.at(index)->setProgress(progress);
    QVector<int> roles{Roles::ProgressRole};
    QModelIndex model_index = createIndex(index, index);
    emit dataChanged(model_index, model_index,roles);
}

void TasksListModel::update_limit_date(int index, int update)
{
    if(indexIsNotValid(index)) return;
    if(update == 0) return;

    auto date = tasks.at(index)->getLimitDate();

    if(update > 0) date = date.addDays(1);
    if(update < 0) date = date.addDays(-1);

    tasks.at(index)->setLimitDate(date);
    QVector<int> roles{Roles::LimitDateRole};
    QModelIndex model_index = createIndex(index, index);
    emit dataChanged(model_index, model_index,roles);
}

void TasksListModel::add(Task* task)
{
    beginInsertRows(QModelIndex(), tasks.size(), tasks.size());
    tasks.append(task);
    endInsertRows();
}

OrganizerDocumentView::OrganizerDocumentView(QWidget* parent)
    :DocumentView(parent)
{
    auto layout = new QVBoxLayout(this);
    setLayout(layout);

    quickWidget = new QQuickWidget(this);
    layout->addWidget(quickWidget);
    model = new TasksListModel(this);
    quickWidget->rootContext()->setContextProperty("model_tasks", model);
    quickWidget->setSource(QUrl("qrc:/Qml/QmlOrganizer.qml"));

    quickWidget->setResizeMode(QQuickWidget::SizeViewToRootObject);

    auto pRoot = quickWidget->rootObject();
    if(pRoot && parent)
    {
        pRoot->setProperty("width_",parent->size().width() - 10);
        pRoot->setProperty("height_",parent->size().height() - 10);
    }
}

bool OrganizerDocumentView::openDocument(QFile &file, ReadableWritable rw)
{
    Q_UNUSED(rw);

    if(!file.isOpen()) return false;

    QXmlStreamReader xmlReader(&file);

    Task* task = nullptr;
    int size = 0;
    while(!xmlReader.atEnd() && !xmlReader.hasError())
    {
        auto element = xmlReader.readNext();

        if(element == QXmlStreamReader::StartElement)
        {
            qDebug() << xmlReader.name();
            if(xmlReader.name() == "numbertasks") {
                auto attr = xmlReader.attributes();
                size = attr.value("size").toInt();
                qDebug() << "numbertasks = " << size;
            }

            for(int i = 0; i < size; ++i)
                if(xmlReader.name() == "task_" + QString::number(i)) {
                    qDebug() << xmlReader.name();

                    auto attr = xmlReader.attributes();

                    if(attr.value("name").isEmpty()) continue;
                    auto name = attr.value("name").toString();
                    qDebug() << xmlReader.name() << name;

                    if(attr.value("description").isEmpty()) continue;
                    auto description = attr.value("description").toString();
                    qDebug() << xmlReader.name() << description;

                    if(attr.value("progress").isEmpty()) continue;
                    auto progress = attr.value("progress").toInt();
                    qDebug() << xmlReader.name() << progress;

                    if(attr.value("limitDate").isEmpty()) continue;
                    auto limitDate = QDate::fromString(attr.value("limitDate").toString());
                    qDebug() << xmlReader.name() << limitDate;

                    task = new Task(this);
                    if(task)
                    {
                        task->setName(name);
                        task->setDescription(description);
                        task->setProgress(progress);
                        task->setLimitDate(limitDate);
                        model->add(task);
                    }
                }
        }
    }

    if(xmlReader.hasError())
    {
        qDebug() << "Error xmlReader:" << xmlReader.error();
    }

    qDebug() << "openDocument return true";

    fileName = file.fileName();
    setWindowTitle(fileName.section('/',-1));

    return true;
}

bool OrganizerDocumentView::saveDocument(QFile &file)
{
    if(!file.isOpen()) return false;

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);

    xmlWriter.writeStartDocument();

    auto list = model->getListTask();

    xmlWriter.writeStartElement("numbertasks");
    xmlWriter.writeAttribute("size", QString::number(list.length()));

    int i = 0;
    for(const auto& a: model->getListTask())
    {
        xmlWriter.writeStartElement("task_" + QString::number(i));

        xmlWriter.writeAttribute("name", a->getName());
        xmlWriter.writeAttribute("description", a->getDescription());
        xmlWriter.writeAttribute("progress", QString::number(a->getProgress()));
        xmlWriter.writeAttribute("limitDate", a->getLimitDate().toString());

        xmlWriter.writeEndElement(); // task
        ++i;
    }

    xmlWriter.writeEndElement(); // numbertasks
    xmlWriter.writeEndDocument();

    fileName = file.fileName();
    setWindowTitle(fileName.section('/',-1));

    return true;
}

void OrganizerDocumentView::print(QPrinter *printer) const
{
    Q_UNUSED(printer);
}

bool OrganizerDocumentView::isTypeDoc(TypeDocumentView type) const
{
    return type == TypeDocumentView::OrganizerDocumentView ? true: false;
}

bool OrganizerDocumentView::eventFilter(QObject *obj, QEvent *event)
{
    switch(event->type())
    {
        case QEvent::Close:
        {
            QMdiSubWindow* subWindow = dynamic_cast<QMdiSubWindow*>(obj);
            if(subWindow == nullptr) break;
            emit closeSubWnd(TypeDocumentView::OrganizerDocumentView);
            break;
        }
        default:
            break;
    }

    return QObject::eventFilter(obj, event);
}

void OrganizerDocumentView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    auto pRoot = quickWidget->rootObject();
    if(pRoot)
    {
        pRoot->setProperty("width_",parentWidget()->size().width() - 10);
        pRoot->setProperty("height_",parentWidget()->size().height() - 10);
    }
}

DocumentView *CreatorOrganizerDocumentView::newDocumentView(QWidget *parent)
{
    return new OrganizerDocumentView(parent);
}

DocumentView *CreatorOrganizerDocumentView::openDocumentView(QString &aFileName, QWidget *parent, ReadableWritable rw)
{
    if(aFileName.isEmpty()) return nullptr;

    qDebug() << aFileName;

    QString ext = OrganizerDocumentView::extention();
    int index = aFileName.indexOf(ext);
    if(index == -1 || aFileName.length() - ext.length() != index) return nullptr;

    qDebug() << ext;

    QFile file(aFileName);
    if(!file.open(QFile::ReadOnly | QFile::ExistingOnly)) return nullptr;

    qDebug() << aFileName << "opened";

    auto docView = new OrganizerDocumentView(nullptr);
    if(docView == nullptr) return nullptr;

    qDebug() << "docView created";

    bool opened = docView->openDocument(file,rw);

    file.close();

    qDebug() << aFileName << "closed";

    if(!opened)
    {
        delete docView;
        return nullptr;
    }

    docView->setParent(parent);
    return docView;
}

bool CreatorOrganizerDocumentView::saveDocumentView(QString &aFileName, DocumentView &docView)
{
    if(aFileName.isEmpty()) return false;

    QFile file(aFileName);
    if(!file.open(QFile::WriteOnly | QFile::Truncate)) return false;

    docView.saveDocument(file);
    file.close();

    return true;
}

void CreatorOrganizerDocumentView::fun() {}


