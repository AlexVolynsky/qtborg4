#-------------------------------------------------
#
# Project created by QtCreator 2018-07-11T07:22:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtborg4
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    generaltab.cpp \
    loggingcategories.cpp

HEADERS  += mainwindow.h \
    generaltab.h \
    loggingcategories.h

FORMS    +=

DISTFILES += \
    README.md
