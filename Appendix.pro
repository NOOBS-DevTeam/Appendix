#-------------------------------------------------
#
# Project created by QtCreator 2013-01-25T22:06:03
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Appendix
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    SyntaxHighlighter.cpp \
    Editor.cpp \
    settingsdialog.cpp \
    helpdialog.cpp

HEADERS  += mainwindow.h \
    SyntaxHighlighter.h \
    Editor.h \
    settingsdialog.h \
    helpdialog.h

FORMS    += mainwindow.ui \
    settingsdialog.ui \
    helpdialog.ui

OTHER_FILES += \
    stop.ico \
    save_as.ico \
    save.ico \
    play.ico \
    open.ico

RESOURCES += \
    resources.qrc
