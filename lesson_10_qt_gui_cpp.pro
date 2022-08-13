QT       += core gui printsupport quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TRANSLATIONS += QtLanguage_ru.ts QtLanguage_en.ts
CODECFORSRC = UTF-8

SOURCES += \
    src/documentview.cpp \
    src/drawgraphtoolbarsingleton.cpp \
    src/graphdocumentview.cpp \
    src/keypresseventfilter.cpp \
    src/languagevisitor.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/organizerdocumentview.cpp \
    src/textdocumentview.cpp \
    src/textformatetoolbarsingleton.cpp \
    src/toolbarelementsfactory.cpp \
    src/widgetsettings.cpp \
    src/widgettreedirs.cpp

HEADERS += \
    inc/documentview.h \
    inc/drawgraphtoolbarsingleton.h \
    inc/keypresseventfilter.h \
    inc/languagevisitor.h \
    inc/mainwindow.h \
    inc/organizerdocumentview.h \
    inc/textformatetoolbarsingleton.h \
    inc/widgetsettings.h \
    inc/widgettreedirs.h \
    inc/toolbarelementsfactory.h \
    inc/graphdocumentview.h \
    inc/textdocumentview.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    help.qrc \
    icons.qrc \
    language.qrc \
    qml.qrc \
    styles.qrc

SUBDIRS = \
    $${PWD}/tests/test_task/
