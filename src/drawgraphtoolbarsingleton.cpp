#include "inc/drawgraphtoolbarsingleton.h"
#include "inc/toolbarelementsfactory.h"
#include "QDebug"

extern template std::optional<QAction *> WidgetsFactory<QAction>::create(const QString &&nameObject, QWidget *parent, bool checkable, const QPixmap &&icon);
extern template void WidgetsFactory<QAction>::setText(QObject* parent,const QString&& nameObject,const QString&& text);
extern template std::optional<QComboBox *> WidgetsFactory<QComboBox>::create(const QString &&nameObject, QWidget *parent, bool checkable, const QPixmap &&icon);
extern template void WidgetsFactory<QComboBox>::setText(QObject* parent,const QString&& nameObject,const QString&& text);

DrawGraphToolBarSingleton* DrawGraphToolBarSingleton::getInstance(MainWindow* parent)
{
    static DrawGraphToolBarSingleton* theInstance =
            new DrawGraphToolBarSingleton(parent);
    return theInstance;
}

void DrawGraphToolBarSingleton::retranslate()
{
    WidgetsFactory<QAction>::setText(this,"actDrawElipse",tr("Элипс"));
    WidgetsFactory<QAction>::setText(this,"actDrawRectangle",tr("Прямоугольник"));
    WidgetsFactory<QAction>::setText(this,"actDrawStar",tr("Звезда"));
    WidgetsFactory<QComboBox>::setText(this,"cbWidthPen",tr("Толщина пера"));
    WidgetsFactory<QAction>::setText(this,"actColorGraphItemBorder",tr("Цвет границы элемента"));
    WidgetsFactory<QAction>::setText(this,"actColorGraphItem",tr("Цвет элемента"));
}

DrawGraphToolBarSingleton::DrawGraphToolBarSingleton(MainWindow *parent)
    : QToolBar(parent)
{
    auto act = WidgetsFactory<QAction>::create(
                "actDrawElipse", this,true,QPixmap(":/icons/graphics/elipse.png"));
    Q_ASSERT(act != nullptr);
    connect(*act,SIGNAL(triggered()),this,SLOT(setDrawingElipse()));
    addAction(*act);

    act = WidgetsFactory<QAction>::create(
                    "actDrawRectangle",this,true,QPixmap(":/icons/graphics/rectangle.png"));
    Q_ASSERT(act != nullptr);
    connect(*act,SIGNAL(triggered()),this,SLOT(setDrawingRectangle()));
    addAction(*act);

    act = WidgetsFactory<QAction>::create(
                    "actDrawStar",this,true,QPixmap(":/icons/graphics/star.png"));
    Q_ASSERT(act != nullptr);
    connect(*act,SIGNAL(triggered()),this,SLOT(setDrawingStar()));
    addAction(*act);

    auto combo = WidgetsFactory<QComboBox>::create(
                    "cbWidthPen",this,false,QPixmap());
    Q_ASSERT(combo != nullptr);

    QStringList listItems;
    listItems << "1" << "2" << "3";
    (*combo)->addItems(listItems);
    connect(*combo, QOverload<int>::of(&QComboBox::activated),
        this,&DrawGraphToolBarSingleton::setWidthPen);
    addWidget(*combo);

    act = WidgetsFactory<QAction>::create(
                    "actColorGraphItemBorder",this,false,QPixmap(":/icons/graphics/colorgraphitemborder.png"));
    Q_ASSERT(act != nullptr);
    connect(*act,SIGNAL(triggered()),this,SLOT(setColorBorder()));
    addAction(*act);

    act = WidgetsFactory<QAction>::create(
                    "actColorGraphItem",this,false,QPixmap(":/icons/graphics/colorgraphitem.png"));
    Q_ASSERT(act != nullptr);
    connect(*act,SIGNAL(triggered()),this,SLOT(setColor()));
    addAction(*act);
}

std::optional<GraphDocumentView*> DrawGraphToolBarSingleton::getCurrentGraphDocView() const
{
    auto wnd = qobject_cast<MainWindow*>(parent());
    if(!wnd) return std::nullopt;
    auto optDocView = wnd->currentSubWindow();
    if(!optDocView) return std::nullopt;
    auto graphDocView = qobject_cast<GraphDocumentView*>(*optDocView);
    if(!graphDocView) return std::nullopt;

    return std::make_optional<GraphDocumentView*>(graphDocView);
}

void DrawGraphToolBarSingleton::setDrawingElement(QString&& objName, GraphDocumentView::TypeGraphElement typeGraphElement)
{
    auto graphDocView = getCurrentGraphDocView();
    if(!graphDocView) return;

    if(WidgetsFactory<QAction>::isChecked(this,std::move(objName)))
    {
        (*graphDocView)->setTypeGraphElement(typeGraphElement);
        setActionsChecked(typeGraphElement);
        return;
    }

    (*graphDocView)->setTypeGraphElement(GraphDocumentView::TypeGraphElement::Empty);
    setActionsChecked(GraphDocumentView::TypeGraphElement::Empty);
}

void DrawGraphToolBarSingleton::setActionsChecked(GraphDocumentView::TypeGraphElement typeGraphElement)
{
    qDebug() << "setActionsChecked(" << typeGraphElement <<")";

    WidgetsFactory<QAction>::setChecked(this,"actDrawElipse",false);
    WidgetsFactory<QAction>::setChecked(this,"actDrawRectangle",false);
    WidgetsFactory<QAction>::setChecked(this,"actDrawStar",false);

    switch (typeGraphElement) {
    case GraphDocumentView::TypeGraphElement::Ellipse:
        WidgetsFactory<QAction>::setChecked(this,"actDrawElipse",true);
        break;
    case GraphDocumentView::TypeGraphElement::Rectangle:
        WidgetsFactory<QAction>::setChecked(this,"actDrawRectangle",true);
        break;
    case GraphDocumentView::TypeGraphElement::Star:
        WidgetsFactory<QAction>::setChecked(this,"actDrawStar",true);
        break;
    case GraphDocumentView::TypeGraphElement::Empty:
        break;
    }
}

void DrawGraphToolBarSingleton::setDrawingElipse()
{
    setDrawingElement("actDrawElipse",GraphDocumentView::TypeGraphElement::Ellipse);
}

void DrawGraphToolBarSingleton::setDrawingRectangle()
{
    setDrawingElement("actDrawRectangle",GraphDocumentView::TypeGraphElement::Rectangle);
}

void DrawGraphToolBarSingleton::setDrawingStar()
{
    setDrawingElement("actDrawStar",GraphDocumentView::TypeGraphElement::Star);
}

void DrawGraphToolBarSingleton::setColor()
{
    auto graphDocView = getCurrentGraphDocView();
    if(!graphDocView) return;

    (*graphDocView)->setColorBrush(QColorDialog::getColor());
}

void DrawGraphToolBarSingleton::setColorBorder()
{
    auto graphDocView = getCurrentGraphDocView();
    if(!graphDocView) return;

    (*graphDocView)->setPenColor(QColorDialog::getColor());
}

void DrawGraphToolBarSingleton::setWidthPen(int index)
{
    auto graphDocView = getCurrentGraphDocView();
    if(!graphDocView) return;

    switch(index)
    {
    case 0:
        (*graphDocView)->setPenWidth(2);
        break;
    case 1:
        (*graphDocView)->setPenWidth(5);
        break;
    case 2:
        (*graphDocView)->setPenWidth(10);
        break;
    }
}

void DrawGraphToolBarSingleton::activatedDocumentView(DocumentView* docView)
{
    if(!docView) return;
    auto graphDocView = qobject_cast<GraphDocumentView*>(docView);
    if(!graphDocView) return;

    //setActionsChecked(textDocView->te().alignment());
}
