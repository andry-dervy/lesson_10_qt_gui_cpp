QT += testlib widgets printsupport quickwidgets
QT += gui
CONFIG += qt warn_on depend_includepath testcase
CONFIG += c++17

TEMPLATE = app

HEADERS += \
    ../../inc/documentview.h \
    ../../inc/drawgraphtoolbarsingleton.h \
    ../../inc/keypresseventfilter.h \
    ../../inc/languagevisitor.h \
    ../../inc/mainwindow.h \
    ../../inc/organizerdocumentview.h \
    ../../inc/textformatetoolbarsingleton.h \
    ../../inc/widgetsettings.h \
    ../../inc/widgettreedirs.h \
    ../../inc/toolbarelementsfactory.h \
    ../../inc/graphdocumentview.h \
    ../../inc/textdocumentview.h

SOURCES += tst_taskslistmodel.cpp \
    ../../src/documentview.cpp \
    ../../src/drawgraphtoolbarsingleton.cpp \
    ../../src/graphdocumentview.cpp \
    ../../src/keypresseventfilter.cpp \
    ../../src/languagevisitor.cpp \
    ../../src/mainwindow.cpp \
    ../../src/organizerdocumentview.cpp \
    ../../src/textdocumentview.cpp \
    ../../src/textformatetoolbarsingleton.cpp \
    ../../src/toolbarelementsfactory.cpp \
    ../../src/widgetsettings.cpp \
    ../../src/widgettreedirs.cpp

FORMS += \
    ../../mainwindow.ui

INCLUDEPATH = $${PWD}/../../
