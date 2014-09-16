#-------------------------------------------------
#
# Project created by QtCreator 2014-09-16T08:45:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SMarkDown
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    markdownviewer.cpp

HEADERS  += mainwindow.h \
    markdownviewer.h

FORMS    += mainwindow.ui

RESOURCES += \
    icons/icons.qrc
