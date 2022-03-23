#-------------------------------------------------
#
# Project created by QtCreator 2022-02-22T16:46:39
#
#-------------------------------------------------

QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PrinterEdit3_0
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    GraphicsControl\ugraphicsview.cpp \
    GraphicsControl\ugraphicsscene.cpp \
    GraphicsControl\GraphicsItems\graphicsitembase.cpp \
    GraphicsControl\sizehandle.cpp \
    GraphicsControl/GraphicsItems/graphicsrectitem.cpp \
    GraphicsControl/GraphicsItems/graphicsellipseitem.cpp \
    UWidget/rluer.cpp \
    GraphicsControl/GraphicsItems/graphicstextitem.cpp \
    GraphicsControl/GraphicsItems/qgraphicstextitemex.cpp

HEADERS += \
        mainwindow.h \
    GraphicsControl\ugraphicsview.h \
    GraphicsControl\ugraphicsscene.h \
    GraphicsControl\GraphicsItems\graphicsitembase.h \
    GraphicsControl\sizehandle.h \
    GraphicsControl/GraphicsItems/graphicsrectitem.h \
    GraphicsControl/GraphicsItems/graphicsellipseitem.h \
    GraphicsControl\Enums.h \
    UWidget/rluer.h \
    GraphicsControl/dpitool.h \
    GraphicsControl/GraphicsItems/graphicstextitem.h \
    GraphicsControl/GraphicsItems/qgraphicstextitemex.h

FORMS += \
        mainwindow.ui \
    UWidget/rluer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
