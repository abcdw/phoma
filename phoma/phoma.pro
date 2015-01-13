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
    forms/photoform.cpp \
    src/tphoto.cpp \
    src/tsection.cpp \
    src/tuser.cpp \
    forms/registrationform.cpp

HEADERS  += \
    src/tcontroller.h \
    forms/mainpage.h \
    forms/mainwindow.h \
    forms/photoform.h \
    src/tphoto.h \
    src/tsection.h \
    src/tuser.h \
    forms/registrationform.h

FORMS    += \
    forms/mainwindow.ui \
    forms/mainpage.ui \
    forms/photoform.ui \
    forms/registrationform.ui
