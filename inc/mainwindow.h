#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QMdiArea>
#include "QToolBar"

#include <memory>
#include <inc/keypresseventfilter.h>
#include <inc/widgetsettings.h>
#include <inc/widgettreedirs.h>
#include "inc/documentview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class LanguageVisitor;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void retranslate();

    std::optional<DocumentView*> currentSubWindow();

private:
    Ui::MainWindow *ui;

    QString pathDir;
    QDialog* wdtHelp;
    KeyPressEventFilter* keyPressEvent;
    WidgetSettings* wdgtSettings;
    QDockWidget* dockTreeDirs;
    WidgetTreeDirsSingleton* wdgtTreeDirs;
    QToolBar* tbTextFormate;

    ReadableWritable rw;

    QMdiArea* mdi;
    QLabel* statusLabel;
    QAction* changeReadableWritable;

    QMap<QString,CreatorDocumentView*> mapCreators;
    QString fileNameOrganizer;

private:
    void acceptLanguage(std::shared_ptr<LanguageVisitor>&& lv);

    void setMenuFile();
    void setMenuView();
    void setMenuSettings();
    void setMenuLanguage();
    void setMenuHelp();
    void setMenu();
    void setToolBar();

    void loadSettings();
    void saveSettings();

    void retranslateMenuFile();
    void retranslateMenuView();
    void retranslateMenuSettings();
    void retranslateMenuLanguage();
    void retranslateMenuHelp();

    void setReadableWritable(ReadableWritable aRW);
    void setTheme(QString&& nfileQss);
    void switchCheckedActionLanguage(std::shared_ptr<LanguageVisitor>& lv);
    void setVisibleTextFormatToolBar(bool visible);
    void setVisibleDrawGraphToolBar(bool visible);
    void addSubWindow(DocumentView* docView);

signals:
    void activatedDocumentView(DocumentView* docView);

private slots:
    void setRussianLanguage();
    void setEnglishLanguage();

    void setThemeMailSy();
    void setThemeIntegrid();

    void viewTreeDirs();
    void viewToolBarTextFormat();
    void viewToolBarDrawing();

    void newTextFile();
    void newGraphFile();
    void newOrganizerFile();
    void openFilePath(QString& path, ReadableWritable aRW);
    void openFile();
    void openFileReadableOnly();
    void openFilePathFromFileSystemModel(QString& fileName);
    void openFileOrganizerDefault();
    void setCurrentFileOrganizerAsDefault();

    void saveFile();
    void saveFileAs();
    void saveFileAll();

    void printFile();

    void callingHelp();
    void changeReadableWritable_triggered();

    void quit();
    void assignKeyboardShortcuts();
    void subWindowActivated(QMdiSubWindow* subWnd);
    void closeSubWnd(TypeDocumentView type);
    void closeDockTreeDirs();
};

#endif // MAINWINDOW_H
