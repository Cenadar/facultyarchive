#-------------------------------------------------
#
# Project created by QtCreator 2013-03-09T14:50:29
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = facultyarchive
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    authors.cpp \
    faculties.cpp \
    departments.cpp \
    books.cpp

HEADERS  += mainwindow.h \
    authors.h \
    faculties.h \
    departments.h \
    books.h

FORMS    += mainwindow.ui \
    authors.ui \
    faculties.ui \
    departments.ui \
    books.ui
