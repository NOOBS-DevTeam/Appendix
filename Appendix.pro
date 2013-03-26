#-------------------------------------------------
#
# Project created by QtCreator 2013-01-25T22:06:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Appendix
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    SyntaxHighlighter.cpp \
    Editor.cpp \
    settingsdialog.cpp

HEADERS  += mainwindow.h \
    SyntaxHighlighter.h \
    Editor.h \
    settingsdialog.h

FORMS    += mainwindow.ui \
    settingsdialog.ui
