#-------------------------------------------------
#
# Project created by QtCreator 2014-05-24T22:43:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = datasettools2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    robwidget.cpp \
    manager.cpp \
    tagelement.cpp \
readWriteObjectFile.cpp \
FaceObject.cpp

HEADERS  += mainwindow.h \
    robwidget.h \
    manager.h \
    tagelement.h \
readWriteObjectFile.h \
FaceObject.h

FORMS    += mainwindow.ui
