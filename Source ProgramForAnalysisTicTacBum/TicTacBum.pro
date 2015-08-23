#-------------------------------------------------
#
# Project created by QtCreator 2015-08-13T13:36:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TicTacBum
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    HarrixMathLibrary.cpp \
    HarrixQtLibrary.cpp \
    mtrand.cpp

HEADERS  += mainwindow.h \
    HarrixMathLibrary.h \
    HarrixQtLibrary.h \
    mtrand.h

FORMS    += mainwindow.ui
