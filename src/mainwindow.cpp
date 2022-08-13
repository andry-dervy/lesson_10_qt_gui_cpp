#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QTextStream"
#include "QDockWidget"
#include "QMdiSubWindow"
#include "QPrinter"
#include "QToolButton"
#include "QSettings"

#include "inc/mainwindow.h"
#include "inc/languagevisitor.h"
#include "inc/textformatetoolbarsingleton.h"
#include "inc/drawgraphtoolbarsingleton.h"
#include "inc/toolbarelementsfactory.h"
#include "inc/organizerdocumentview.h"

extern template void WidgetsFactory<QAction>::setText(QObject* obj,const QString&& nameObject,const QString&& text);
extern template void WidgetsFactory<QMenu>::setText(QObject* obj,const QString&& nameObject,const QString&& text);
extern template std::optional<QAction *> WidgetsFactory<QAction>::create(const QString &&nameObject, QWidget *parent, bool checkable, const QPixmap &&icon);
extern template std::optional<QMenu *> WidgetsFactory<QMenu>::create(const QString &&nameObject, QWidget *parent, bool checkable, const QPixmap &&icon);
extern template std::optional<QToolButton *> WidgetsFactory<QToolButton>::create(const QString &&nameObject, QWidget *parent, bool checkable, const QPixmap &&icon);
extern template void WidgetsFactory<QToolButton>::setText(QObject* obj,const QString&& nameObject,const QString&& text);

void MainWindow::setMenuFile()
{
    auto menuFile = WidgetsFactory<QMenu>::create("menuFile",this);
    Q_ASSERT(menuFile != nullptr);
    ui->menubar->addMenu(*menuFile);
    auto menuNewFile = WidgetsFactory<QMenu>::create("menuNewFile",this);
    Q_ASSERT(menuFile != nullptr);
    (*menuFile)->addMenu(*menuNewFile);

    auto act = WidgetsFactory<QAction>::create("actNewTextFile",this);
    Q_ASSERT(act != nullptr);
    (*menuNewFile)->addAction(*act);
    connect(*act, &QAction::triggered, this, &MainWindow::newTextFile);
    act = WidgetsFactory<QAction>::create("actNewGraphFile",this);
    Q_ASSERT(act != nullptr);
    (*menuNewFile)->addAction(*act);
    connect(*act, &QAction::triggered, this, &MainWindow::newGraphFile);
    act = WidgetsFactory<QAction>::create("actNewOrganizerFile",this);
    Q_ASSERT(act != nullptr);
    (*menuNewFile)->addAction(*act);
    connect(*act, &QAction::triggered, this, &MainWindow::newOrganizerFile);

    act = WidgetsFactory<QAction>::create("actOpen",this);
    Q_ASSERT(act != nullptr);
    (*menuFile)->addAction(*act);
    connect(*act, &QAction::triggered, this, &MainWindow::openFile);
    act = WidgetsFactory<QAction>::create("actOpenReadableOnly",this);
    Q_ASSERT(act != nullptr);
    (*menuFile)->addAction(*act);
    connect(*act, &QAction::triggered, this, &MainWindow::openFileReadableOnly);

    act = WidgetsFactory<QAction>::create("actSave",this);
    Q_ASSERT(act != nullptr);
    (*menuFile)->addAction(*act);
    connect(*act, &QAction::triggered, this, &MainWindow::saveFile);
    act = WidgetsFactory<QAction>::create("actSaveAs",this);
    Q_ASSERT(act != nullptr);
    (*menuFile)->addAction(*act);
    connect(*act, &QAction::triggered, this, &MainWindow::saveFileAs);
    act = WidgetsFactory<QAction>::create("actSaveAll",this);
    Q_ASSERT(act != nullptr);
    (*menuFile)->addAction(*act);
    connect(*act, &QAction::triggered, this, &MainWindow::saveFileAll);

    act = WidgetsFactory<QAction>::create("actPrint",this);
    Q_ASSERT(act != nullptr);
    (*menuFile)->addAction(*act);
    connect(*act, &QAction::triggered, this, &MainWindow::printFile);
}
void MainWindow::setMenuView()
{
    auto menuView = WidgetsFactory<QMenu>::create("menuView",this);
    Q_ASSERT(menuView != nullptr);
    ui->menubar->addMenu(*menuView);
    auto act = WidgetsFactory<QAction>::create("actViewTreeDirs",this,true);
    Q_ASSERT(act != nullptr);
    (*act)->setChecked(false);
    (*menuView)->addAction(*act);
    connect(*act, &QAction::triggered, this, &MainWindow::viewTreeDirs);
    act = WidgetsFactory<QAction>::create("actViewToolBarTextFormat",this,true);
    Q_ASSERT(act != nullptr);
    (*act)->setChecked(false);
    (*menuView)->addAction(*act);
    connect(*act, &QAction::triggered, this, &MainWindow::viewToolBarTextFormat);
    act = WidgetsFactory<QAction>::create("actViewToolBarDrawing",this,true);
    Q_ASSERT(act != nullptr);
    (*act)->setChecked(false);
    (*menuView)->addAction(*act);
    connect(*act, &QAction::triggered, this, &MainWindow::viewToolBarDrawing);
}
void MainWindow::setMenuSettings()
{
    auto menuSettings = WidgetsFactory<QMenu>::create("menuSettings",this);
    Q_ASSERT(menuSettings != nullptr);
    ui->menubar->addMenu(*menuSettings);
    auto act = WidgetsFactory<QAction>::create("actAssignKeyboardShortcuts",this);
    Q_ASSERT(act != nullptr);
    (*menuSettings)->addAction(*act);
    connect(*act, &QAction::triggered, this, &MainWindow::assignKeyboardShortcuts);

    auto menuTheme = WidgetsFactory<QMenu>::create("menuTheme",this);
    Q_ASSERT(menuTheme != nullptr);
    (*menuSettings)->addMenu(*menuTheme);
    act = WidgetsFactory<QAction>::create("actThemeMailSy",this);
    Q_ASSERT(act != nullptr);
    (*menuTheme)->addAction(*act);
    connect(*act, &QAction::triggered, this, &MainWindow::setThemeMailSy);
    act = WidgetsFactory<QAction>::create("actThemeIntegrid",this);
    Q_ASSERT(act != nullptr);
    (*menuTheme)->addAction(*act);
    connect(*act, &QAction::triggered, this, &MainWindow::setThemeIntegrid);

    (*menuSettings)->addSeparator();

    act = WidgetsFactory<QAction>::create("actOpenFileOrganizer",this,true);
    Q_ASSERT(act != nullptr);
    (*menuSettings)->addAction(*act);
    connect(*act, &QAction::triggered, this, &MainWindow::openFileOrganizerDefault);
    act = WidgetsFactory<QAction>::create("actSetCurrentFileOrganizerAsDefault",this);
    Q_ASSERT(act != nullptr);
    (*menuSettings)->addAction(*act);
    connect(*act, &QAction::triggered, this, &MainWindow::setCurrentFileOrganizerAsDefault);
}
void MainWindow::setMenuLanguage()
{
    auto menuLanguage = WidgetsFactory<QMenu>::create("menuLanguage",this);
    Q_ASSERT(menuLanguage != nullptr);
    ui->menubar->addMenu(*menuLanguage);
    auto act = WidgetsFactory<QAction>::create("actRussian",this,true);
    Q_ASSERT(act != nullptr);
    (*menuLanguage)->addAction(*act);
    connect(*act, &QAction::triggered, this, &MainWindow::setRussianLanguage);
    act = WidgetsFactory<QAction>::create("actEnglish",this,true);
    Q_ASSERT(act != nullptr);
    (*menuLanguage)->addAction(*act);
    connect(*act, &QAction::triggered, this, &MainWindow::setEnglishLanguage);
}
void MainWindow::setMenuHelp()
{
    auto menuHelp = WidgetsFactory<QMenu>::create("menuHelp",this);
    Q_ASSERT(menuHelp != nullptr);
    ui->menubar->addMenu(*menuHelp);
    auto act = WidgetsFactory<QAction>::create("actCallingHelp",this);
    Q_ASSERT(act != nullptr);
    (*menuHelp)->addAction(*act);
    connect(*act, &QAction::triggered, this, &MainWindow::callingHelp);
}
void MainWindow::setMenu()
{
    setMenuFile();
    setMenuView();
    setMenuSettings();
    setMenuLanguage();
    setMenuHelp();

    setThemeIntegrid();
}

void MainWindow::setToolBar()
{
    auto toptb = new QToolBar(this);
    Q_ASSERT(toptb != nullptr);
    addToolBar(Qt::TopToolBarArea,toptb);

    auto tb_newFile = WidgetsFactory<QToolButton>::create("menuHelp",this,false,QPixmap(":/icons/new.png"));
    Q_ASSERT(tb_newFile != nullptr);
    (*tb_newFile)->setPopupMode(QToolButton::MenuButtonPopup);
    toptb->addWidget(*tb_newFile);

    auto menuNewFile = findChild<QMenu*>("menuNewFile");
    Q_ASSERT(menuNewFile != nullptr);
    (*tb_newFile)->setMenu(menuNewFile);

    auto act = WidgetsFactory<QAction>::create("toolBarOpenFile",this,false,QPixmap(":/icons/open.png"));
    Q_ASSERT(act != nullptr);
    toptb->addAction(*act);
    connect(*act, &QAction::triggered, this, &MainWindow::openFile);
    act = WidgetsFactory<QAction>::create("toolBarSaveFile",this,false,QPixmap(":/icons/save.png"));
    Q_ASSERT(act != nullptr);
    toptb->addAction(*act);
    connect(*act, &QAction::triggered, this, &MainWindow::saveFile);
    act = WidgetsFactory<QAction>::create("toolBarPrintFile",this,false,QPixmap(":/icons/print.png"));
    Q_ASSERT(act != nullptr);
    toptb->addAction(*act);
    connect(*act, &QAction::triggered, this, &MainWindow::printFile);

    toptb->addSeparator();

    act = WidgetsFactory<QAction>::create("changeReadableWritable",this,false,QPixmap(":/icons/print.png"));
    Q_ASSERT(act != nullptr);
    changeReadableWritable = *act;
    toptb->addAction(*act);
    connect(*act, &QAction::triggered, this, &MainWindow::changeReadableWritable_triggered);
    setReadableWritable(ReadableWritable::WRITABLE);

    addToolBar(Qt::TopToolBarArea,TextFormateToolBarSingleton::getInstance(this));
    TextFormateToolBarSingleton::getInstance(this)->setAdded();
    TextFormateToolBarSingleton::getInstance(this)->setVisible(false);
    connect(this, &MainWindow::activatedDocumentView,
            TextFormateToolBarSingleton::getInstance(this), &TextFormateToolBarSingleton::activatedDocumentView);

    addToolBar(Qt::TopToolBarArea,DrawGraphToolBarSingleton::getInstance(this));
    DrawGraphToolBarSingleton::getInstance(this)->setAdded();
    DrawGraphToolBarSingleton::getInstance(this)->setVisible(false);
    connect(this, &MainWindow::activatedDocumentView,
            DrawGraphToolBarSingleton::getInstance(this), &DrawGraphToolBarSingleton::activatedDocumentView);
}

void MainWindow::loadSettings()
{
    QSettings settings("app.ini", QSettings::IniFormat);
    auto actOpenFileOrganizer = findChild<QAction*>("actOpenFileOrganizer");
    if(actOpenFileOrganizer != nullptr)
    {
        actOpenFileOrganizer->setChecked(settings.value("OpenFileOrganizerIsChecked").toBool());
        fileNameOrganizer = settings.value("FileNameOrganizer").toString();
    }
}

void MainWindow::saveSettings()
{
    QSettings settings("app.ini", QSettings::IniFormat);

    auto actOpenFileOrganizer = findChild<QAction*>("actOpenFileOrganizer");
    if(actOpenFileOrganizer != nullptr)
    {
        settings.setValue("OpenFileOrganizerIsChecked", actOpenFileOrganizer->isChecked());
        settings.setValue("FileNameOrganizer", fileNameOrganizer);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pathDir(QDir::currentPath())
    , wdtHelp(nullptr)
    , keyPressEvent(new KeyPressEventFilter(this))
    , wdgtSettings(nullptr)
    , dockTreeDirs(nullptr)
    , wdgtTreeDirs(nullptr)
    , tbTextFormate(nullptr)
{
    ui->setupUi(this);

    mdi = new QMdiArea(this);
    mdi->setViewMode(QMdiArea::ViewMode::TabbedView);
    connect(mdi, &QMdiArea::subWindowActivated, this, &MainWindow::subWindowActivated);
    setCentralWidget(mdi);

    statusLabel = new QLabel(this);
    statusBar()->addWidget(statusLabel);

    installEventFilter(keyPressEvent);
    connect(keyPressEvent, &KeyPressEventFilter::newFile, this, &MainWindow::newOrganizerFile);
    connect(keyPressEvent, &KeyPressEventFilter::openFile, this, &MainWindow::openFile);
    connect(keyPressEvent, &KeyPressEventFilter::saveFile, this, &MainWindow::saveFile);
    connect(keyPressEvent, &KeyPressEventFilter::quit, this, &MainWindow::quit);

    setMenu();
    setToolBar();

    setRussianLanguage();

    mapCreators.insert(TextDocumentView::extention(),new CreatorTextDocumentView(this));
    mapCreators.insert(GraphDocumentView::extention(),new CreatorGraphDocumentView(this));
    mapCreators.insert(OrganizerDocumentView::extention(),new CreatorOrganizerDocumentView(this));

    loadSettings();
    openFileOrganizerDefault();
}

MainWindow::~MainWindow()
{
    saveFileAll();
    saveSettings();
    delete ui;
}

void MainWindow::addSubWindow(DocumentView* docView)
{
    if(docView == nullptr) return;

    auto subwnd = mdi->addSubWindow(docView);
    subwnd->installEventFilter(docView);
    connect(docView,&DocumentView::closeSubWnd,this,&MainWindow::closeSubWnd);
    TextFormateToolBarSingleton::getInstance(this)->addTextDocumentView(docView);
    docView->show();
}

void MainWindow::newTextFile()
{
    auto creator = mapCreators.value(TextDocumentView::extention());
    DocumentView* docView = creator->newDocumentView(mdi);
    addSubWindow(docView);
}

void MainWindow::newGraphFile()
{
    auto creator = mapCreators.value(GraphDocumentView::extention());
    auto docView = creator->newDocumentView(mdi);
    addSubWindow(docView);
}

void MainWindow::newOrganizerFile()
{
    auto creator = mapCreators.value(OrganizerDocumentView::extention());
    auto docView = creator->newDocumentView(mdi);
    addSubWindow(docView);
}

void MainWindow::openFilePath(QString& fileName, ReadableWritable aRW = ReadableWritable::WRITABLE)
{
    auto wnds = mdi->subWindowList();
    for(const auto& wnd: wnds)
    {
        auto docView = qobject_cast<DocumentView*>(wnd->widget());
        if(docView == nullptr) continue;
        if(docView->getFileName() == fileName)
        {
            wnd->setFocus();
            return;
        }
    }

    QFileInfo fi(fileName);
    QString ext = fi.suffix();

    if(mapCreators.find(ext) == mapCreators.end()) return;

    auto docView = mapCreators[ext]->openDocumentView(fileName,mdi,aRW);
    addSubWindow(docView);
    docView->setWindowState(Qt::WindowMaximized);
}

void MainWindow::openFile()
{
    QFileDialog fileDialog;

    QString ext;
    for(auto it = mapCreators.begin(); it != mapCreators.end(); ++it)
    {
        ext += "*." + it.key() + ", ";
    }
    ext.remove(ext.size()-2,2);

    QString fileName = fileDialog.getOpenFileName(this,
        tr("Открыть файл"), pathDir, tr("Файл") + "(" + ext + ")");

    openFilePath(fileName);
    pathDir = fileDialog.directory().absolutePath();
}

void MainWindow::openFileReadableOnly()
{
    QFileDialog fileDialog;

    QString fileName = fileDialog.getOpenFileName(this,
        tr("Открыть файл"), pathDir, tr("Текстовые файлы (*.htxt)"));

    openFilePath(fileName,ReadableWritable::READABLE_ONLY);
    pathDir = fileDialog.directory().absolutePath();
}

void MainWindow::openFilePathFromFileSystemModel(QString& fileName)
{
    openFilePath(fileName);
    pathDir = fileName;
}

void MainWindow::openFileOrganizerDefault()
{
    auto actOpenFileOrganizer = findChild<QAction*>("actOpenFileOrganizer");
    if(actOpenFileOrganizer == nullptr) return;

    if(actOpenFileOrganizer->isChecked() &&
       !fileNameOrganizer.isEmpty()) {
        openFilePath(fileNameOrganizer);
    }
}

void MainWindow::setCurrentFileOrganizerAsDefault()
{
    auto optDocView = currentSubWindow();
    if(!optDocView) return;
    auto docView = *optDocView;
    if(!docView->isTypeDoc(TypeDocumentView::OrganizerDocumentView)) return;

    QString fileName = docView->getFileName();
    if(fileName.isEmpty()) return;

    fileNameOrganizer = fileName;
}

void MainWindow::saveFile()
{
    auto optDocView = currentSubWindow();
    if(!optDocView) return;
    auto docView = *optDocView;

    QString fileName = docView->getFileName();
    if(fileName.isEmpty())
    {
        QFileDialog fileDialog;

        const QString ext = docView->getExtention();
        fileName = fileDialog.getSaveFileName(this,
            tr("Сохранить файл"), pathDir,
            tr("Файл") + "(*." + ext + ")");

        if(fileName.isEmpty()) return;

        int index = fileName.indexOf(ext);
        if(index == -1 || fileName.length() - ext.length() != index)
        {
            fileName += "."+ext;
        }
    }

    auto creator = mapCreators.value(docView->getExtention());
    if(creator) creator->saveDocumentView(fileName,*docView);
}

void MainWindow::saveFileAs()
{
    auto optDocView = currentSubWindow();
    if(!optDocView) return;
    auto docView = *optDocView;

    QFileDialog fileDialog;

    const QString ext = docView->getExtention();
    QString fileName = fileDialog.getSaveFileName(this,
        tr("Сохранить файл как"), pathDir,
        tr("Файл") + "(." + ext + ")");

    if(fileName.isEmpty()) return;

    int index = fileName.indexOf(ext);
    if(index == -1 || fileName.length() - ext.length() != index)
    {
        fileName += "."+ext;
    }

    auto creator = mapCreators.value(docView->getExtention());
    if(creator) creator->saveDocumentView(fileName,*docView);
}

void MainWindow::saveFileAll()
{
    auto wnds = mdi->subWindowList();
    for(const auto& wnd: wnds)
    {
        auto docView = qobject_cast<DocumentView*>(wnd->widget());
        if(docView == nullptr ||
           docView->getFileName().isEmpty()) continue;
        QString fileName = docView->getFileName();
        mapCreators[docView->getExtention()]->saveDocumentView(fileName,*docView);
    }
}

void MainWindow::printFile()
{
    auto optDocView = currentSubWindow();
    if(!optDocView) return;
    auto docView = *optDocView;

    if(!docView->isTypeDoc(TypeDocumentView::TextDocumentView)) return;

    QPrinter printer;
    QPrintDialog dlg(&printer, this);
    dlg.setWindowTitle("Print");
    if (dlg.exec() != QDialog::Accepted)
        return;
    docView->print(&printer);
}

void MainWindow::callingHelp()
{
    if(wdtHelp != nullptr)
    {
        wdtHelp->show();
        return;
    }

    QFile file(":/help/help.txt");
    if(!file.open(QIODevice::OpenModeFlag::ReadOnly)) return;

    wdtHelp = new QDialog(this);
    QTextStream textStream(&file);
    auto textHelp = new QPlainTextEdit(textStream.readAll(),this);
    textHelp->setReadOnly(true);
    auto vBoxLayout = new QVBoxLayout(wdtHelp);
    vBoxLayout->addWidget(textHelp);
    wdtHelp->setLayout(vBoxLayout);
    wdtHelp->setMinimumSize(QSize(200,200));
    retranslate();
    wdtHelp->show();
}

void MainWindow::setReadableWritable(ReadableWritable aRW)
{
    rw = aRW;
    switch (rw) {
    case ReadableWritable::READABLE:
    case ReadableWritable::READABLE_ONLY:
        changeReadableWritable->setIcon(QPixmap(":/icons/readable.png"));
        changeReadableWritable->setIconText(tr("Нередактируемый текст"));
        break;
    case ReadableWritable::WRITABLE:
        changeReadableWritable->setIcon(QPixmap(":/icons/writable.png"));
        changeReadableWritable->setIconText(tr("Редактируемый текст"));
        break;
    }
}

void MainWindow::changeReadableWritable_triggered()
{
    auto wnd = mdi->activeSubWindow();
    if(wnd == nullptr) return;

    auto docView = qobject_cast<DocumentView*>(wnd->widget());
    if(docView == nullptr) return;

    switch (docView->getReadableWritable()) {
    case ReadableWritable::READABLE:
        docView->setReadableWritable(ReadableWritable::WRITABLE);
        break;
    case ReadableWritable::READABLE_ONLY:
        break;
    case ReadableWritable::WRITABLE:
        docView->setReadableWritable(ReadableWritable::READABLE);
        break;
    }
    setReadableWritable(docView->getReadableWritable());
}

void MainWindow::quit()
{
    qApp->quit();
}

void MainWindow::assignKeyboardShortcuts()
{
    if(wdgtSettings != nullptr)
    {
        wdgtSettings->show();
        return;
    }

    wdgtSettings = new WidgetSettings(this);
    connect(wdgtSettings, &WidgetSettings::setHotKey, keyPressEvent, &KeyPressEventFilter::setHotKey);
    wdgtSettings->show();
}

void MainWindow::setVisibleTextFormatToolBar(bool visible)
{
    auto actViewToolBarTextFormat = findChild<QAction*>("actViewToolBarTextFormat");
    if(actViewToolBarTextFormat == nullptr) return;
    TextFormateToolBarSingleton::getInstance(this)->setVisible(visible);
    actViewToolBarTextFormat->setChecked(visible);
}

void MainWindow::setVisibleDrawGraphToolBar(bool visible)
{
    auto actViewToolBarDrawing = findChild<QAction*>("actViewToolBarDrawing");
    if(actViewToolBarDrawing == nullptr) return;
    DrawGraphToolBarSingleton::getInstance(this)->setVisible(visible);
    actViewToolBarDrawing->setChecked(visible);
}

void MainWindow::subWindowActivated(QMdiSubWindow* subWnd)
{
    if(subWnd == nullptr) return;
    auto docView = qobject_cast<DocumentView*>(subWnd->widget());
    if(docView == nullptr) return;

    setReadableWritable(docView->getReadableWritable());
    statusLabel->setText(docView->getFileName());

    setVisibleTextFormatToolBar(docView->isTypeDoc(TypeDocumentView::TextDocumentView));
    setVisibleDrawGraphToolBar(docView->isTypeDoc(TypeDocumentView::GraphDocumentView));

    emit activatedDocumentView(docView);
}

void MainWindow::closeSubWnd(TypeDocumentView type)
{
    switch(type)
    {
    case TypeDocumentView::TextDocumentView:
        setVisibleTextFormatToolBar(false);
        break;
    case TypeDocumentView::GraphDocumentView:
        setVisibleDrawGraphToolBar(false);
        break;
    default:
        break;
    }
}

void MainWindow::closeDockTreeDirs()
{
    dockTreeDirs = nullptr;

    auto actViewTreeDirs = findChild<QAction*>("actViewTreeDirs");
    if(actViewTreeDirs != nullptr) actViewTreeDirs->setChecked(false);
}

void MainWindow::retranslateMenuFile()
{
    WidgetsFactory<QMenu>::setText(this,"menuFile",tr("&Файл"));

    WidgetsFactory<QMenu>::setText(this,"menuNewFile",tr("Новый файл"));
    WidgetsFactory<QAction>::setText(this,"actNewTextFile",tr("Новый текстовый файл"));
    WidgetsFactory<QAction>::setText(this,"actNewGraphFile",tr("Новый графический файл"));
    WidgetsFactory<QAction>::setText(this,"actNewOrganizerFile",tr("Новый файл органайзера"));

    WidgetsFactory<QAction>::setText(this,"actOpen",tr("Открыть файл"));
    WidgetsFactory<QAction>::setText(this,"actOpenReadableOnly",tr("Открыть файл только для чтения"));

    WidgetsFactory<QAction>::setText(this,"actSave",tr("Сохранить файл"));
    WidgetsFactory<QAction>::setText(this,"actSaveAs",tr("Сохранить файл как"));
    WidgetsFactory<QAction>::setText(this,"actSaveAll",tr("Сохранить открытые файлы"));

    WidgetsFactory<QAction>::setText(this,"actPrint",tr("Печатать..."));

    WidgetsFactory<QToolButton>::setText(this,"tb_newFile",tr("Новый файл"));

    WidgetsFactory<QAction>::setText(this,"toolBarOpenFile",tr("Открыть текстовый файл"));
    WidgetsFactory<QAction>::setText(this,"toolBarSaveFile",tr("Сохранить файл"));
    WidgetsFactory<QAction>::setText(this,"toolBarPrintFile",tr("Открыть текстовый файл"));
    WidgetsFactory<QAction>::setText(this,"toolBarOpenFile",tr("Печатать файл"));

    setReadableWritable(rw);
}
void MainWindow::retranslateMenuView()
{
    auto menuView = findChild<QMenu*>("menuView");
    if(menuView != nullptr) menuView->setTitle(tr("&Вид"));
    auto actViewTreeDirs = findChild<QAction*>("actViewTreeDirs");
    if(actViewTreeDirs != nullptr) actViewTreeDirs->setText(tr("Дерево каталогов"));
    auto actViewToolBarTextFormat = findChild<QAction*>("actViewToolBarTextFormat");
    if(actViewToolBarTextFormat != nullptr) actViewToolBarTextFormat->setText(tr("Формат текста"));
    WidgetsFactory<QAction>::setText(this,"actViewToolBarDrawing",tr("Рисование"));
}
void MainWindow::retranslateMenuSettings()
{
    auto menuSettings = findChild<QMenu*>("menuSettings");
    if(menuSettings != nullptr) menuSettings->setTitle(tr("&Настройки"));
    auto actAssignKeyboardShortcuts = findChild<QAction*>("actAssignKeyboardShortcuts");
    if(actAssignKeyboardShortcuts != nullptr) actAssignKeyboardShortcuts->setText(tr("&Установка горячик клавиш"));
    auto menuTheme = findChild<QMenu*>("menuTheme");
    if(menuTheme != nullptr) menuTheme->setTitle(tr("&Выбор темы"));
    auto actThemeMailSy = findChild<QAction*>("actThemeMailSy");
    if(actThemeMailSy != nullptr) actThemeMailSy->setText(tr("Тема MailSy"));
    auto actThemeIntegrid = findChild<QAction*>("actThemeIntegrid");
    if(actThemeIntegrid != nullptr) actThemeIntegrid->setText(tr("Тема Integrid"));
    auto actOpenFileOrganizer = findChild<QAction*>("actOpenFileOrganizer");
    if(actOpenFileOrganizer != nullptr) actOpenFileOrganizer->setText(tr("&Открывать файл органайзера при запуске приложения"));
    auto actSetCurrentFileOrganizerAsDefault = findChild<QAction*>("actSetCurrentFileOrganizerAsDefault");
    if(actSetCurrentFileOrganizerAsDefault != nullptr) actSetCurrentFileOrganizerAsDefault->setText(tr("Установить файл &органайзера по умолчанию"));
}
void MainWindow::retranslateMenuLanguage()
{
    auto menuLanguage = findChild<QMenu*>("menuLanguage");
    if(menuLanguage != nullptr) menuLanguage->setTitle(tr("&Язык интерфейса"));
    auto actRussian = findChild<QAction*>("actRussian");
    if(actRussian != nullptr) actRussian->setText(tr("Русский"));
    auto actEnglish = findChild<QAction*>("actEnglish");
    if(actEnglish != nullptr) actEnglish->setText(tr("Английский"));
}
void MainWindow::retranslateMenuHelp()
{
    auto menuHelp = findChild<QMenu*>("menuHelp");
    if(menuHelp != nullptr) menuHelp->setTitle(tr("&Справка"));
    auto actCallingHelp = findChild<QAction*>("actCallingHelp");
    if(actCallingHelp != nullptr) actCallingHelp->setText(tr("Вызов справки"));
}

void MainWindow::retranslate()
{
    setWindowTitle(tr("Простой текстовый редактор"));

    retranslateMenuFile();
    retranslateMenuView();
    retranslateMenuSettings();
    retranslateMenuLanguage();
    retranslateMenuHelp();

    if(wdtHelp != nullptr)
        wdtHelp->setWindowTitle(tr("Справка"));

    if(wdgtSettings != nullptr)
        wdgtSettings->retranslate();

    if(wdgtTreeDirs != nullptr)
        wdgtTreeDirs->retranslate();

    TextFormateToolBarSingleton::getInstance(this)->retranslate();
    DrawGraphToolBarSingleton::getInstance(this)->retranslate();
}

std::optional<DocumentView*> MainWindow::currentSubWindow()
{
    auto subwindow = mdi->activeSubWindow();
    if(subwindow == nullptr) return std::nullopt;
    if(subwindow->widget() == nullptr) return std::nullopt;
    DocumentView* docView = qobject_cast<DocumentView*>(subwindow->widget());
    if(docView == nullptr) return std::nullopt;

    return std::make_optional<DocumentView*>(docView);
}

void MainWindow::switchCheckedActionLanguage(std::shared_ptr<LanguageVisitor>& lv)
{
    auto actRussian = findChild<QAction*>("actRussian");
    if(actRussian != nullptr) actRussian->setChecked(lv->isLanguage(LANGUAGE::Russian));
    auto actEnglish = findChild<QAction*>("actEnglish");
    if(actEnglish != nullptr) actEnglish->setChecked(lv->isLanguage(LANGUAGE::English));
}

void MainWindow::acceptLanguage(std::shared_ptr<LanguageVisitor>&& lv)
{
    lv->retranslate(this);
    switchCheckedActionLanguage(lv);
}

void MainWindow::setRussianLanguage()
{
    acceptLanguage(std::make_shared<LanguageRussianVisitor>());
}

void MainWindow::setEnglishLanguage()
{
    acceptLanguage(std::make_shared<LanguageEnglishVisitor>());
}

void MainWindow::setTheme(QString&& nfileQss)
{
    QFile fileQss(nfileQss);
    if(!fileQss.open(QFile::ReadOnly)) return;

    QTextStream stream(&fileQss);
    setStyleSheet(stream.readAll());

    auto listwnd = mdi->subWindowList();
    for (auto& wnd: listwnd) {
        if(wnd) wnd->setStyleSheet(stream.readAll());
    }

    fileQss.close();
}

void MainWindow::setThemeMailSy()
{
    setTheme(":/styles/MailSy.qss");

    auto actThemeMailSy = findChild<QAction*>("actThemeMailSy");
    if(actThemeMailSy != nullptr) actThemeMailSy->setIcon(QPixmap(":/icons/enable.png"));
    auto actThemeIntegrid = findChild<QAction*>("actThemeIntegrid");
    if(actThemeIntegrid != nullptr) actThemeIntegrid->setIcon(QPixmap());
}

void MainWindow::setThemeIntegrid()
{
    setTheme(":/styles/Integrid.qss");

    auto actThemeMailSy = findChild<QAction*>("actThemeMailSy");
    if(actThemeMailSy != nullptr) actThemeMailSy->setIcon(QPixmap());
    auto actThemeIntegrid = findChild<QAction*>("actThemeIntegrid");
    if(actThemeIntegrid != nullptr) actThemeIntegrid->setIcon(QPixmap(":/icons/enable.png"));
}

void MainWindow::viewTreeDirs()
{
    if(dockTreeDirs == nullptr)
    {
        auto wdgtTreeDirs = WidgetTreeDirsSingleton::getInstance(this);
        connect(wdgtTreeDirs, &WidgetTreeDirsSingleton::openFile, this, &MainWindow::openFilePathFromFileSystemModel);
        dockTreeDirs = new QDockWidget(this);
        dockTreeDirs->setWidget(wdgtTreeDirs);
        auto ef = new TreeDirsEventFilter();
        dockTreeDirs->installEventFilter(ef);
        connect(ef, &TreeDirsEventFilter::closeDock, this, &MainWindow::closeDockTreeDirs);
    }

    addDockWidget(Qt::LeftDockWidgetArea, dockTreeDirs);

    auto actViewTreeDirs = findChild<QAction*>("actViewTreeDirs");
    if(actViewTreeDirs != nullptr) actViewTreeDirs->setChecked(true);
}

void MainWindow::viewToolBarTextFormat()
{
    if(!TextFormateToolBarSingleton::getInstance(this)->isAdded())
    {
        addToolBar(Qt::TopToolBarArea,TextFormateToolBarSingleton::getInstance(this));
        TextFormateToolBarSingleton::getInstance(this)->setAdded();
    }

    auto actViewToolBarTextFormate = findChild<QAction*>("actViewToolBarTextFormat");
    if(actViewToolBarTextFormate == nullptr) return;
    if(!actViewToolBarTextFormate->isChecked())
    {
        TextFormateToolBarSingleton::getInstance(this)->setVisible(false);
        actViewToolBarTextFormate->setChecked(false);
    }
    else
    {
        TextFormateToolBarSingleton::getInstance(this)->setVisible(true);
        actViewToolBarTextFormate->setChecked(true);
    }
}

void MainWindow::viewToolBarDrawing()
{
    if(!DrawGraphToolBarSingleton::getInstance(this)->isAdded())
    {
        addToolBar(Qt::TopToolBarArea,DrawGraphToolBarSingleton::getInstance(this));
        DrawGraphToolBarSingleton::getInstance(this)->setAdded();
    }

    auto actViewToolBarDrawing = findChild<QAction*>("actViewToolBarDrawing");
    if(actViewToolBarDrawing == nullptr) return;
    if(!actViewToolBarDrawing->isChecked())
    {
        DrawGraphToolBarSingleton::getInstance(this)->setVisible(false);
        actViewToolBarDrawing->setChecked(false);
    }
    else
    {
        DrawGraphToolBarSingleton::getInstance(this)->setVisible(true);
        actViewToolBarDrawing->setChecked(true);
    }
}

