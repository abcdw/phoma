#-------------------------------------------------
#
# Project created by QtCreator 2014-12-17T17:08:54
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = phoma
TEMPLATE = app


SOURCES +=\
    src/main.cpp \
    src/tcontroller.cpp \
    forms/mainpage.cpp \
    forms/mainwindow.cpp \
    forms/photoform.cpp

HEADERS  += \
    src/tcontroller.h \
    forms/mainpage.h \
    forms/mainwindow.h \
    forms/photoform.h

FORMS    += \
    forms/mainwindow.ui \
    forms/mainpage.ui \
    forms/photoform.ui
