#-------------------------------------------------
#
# Project created by QtCreator 2017-10-14T19:15:17
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = TPO
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    dialog.h

FORMS    += mainwindow.ui \
    dialog.ui
