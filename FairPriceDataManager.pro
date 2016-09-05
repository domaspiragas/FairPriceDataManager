#-------------------------------------------------
#
# Project created by QtCreator 2016-07-24T12:05:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FairPriceDataManager
TEMPLATE = app
RC_FILE = FairPriceDataManager.rc

SOURCES += main.cpp\
        mainwindow.cpp \
    customer.cpp \
    job.cpp \
    car.cpp \
    newcustomer.cpp \
    existingcustomer.cpp

HEADERS  += mainwindow.h \
    customer.h \
    job.h \
    car.h \
    newcustomer.h \
    existingcustomer.h

FORMS    += mainwindow.ui \
    newcustomer.ui \
    existingcustomer.ui

RESOURCES += \
    images.qrc
