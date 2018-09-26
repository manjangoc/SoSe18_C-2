QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mehr_maeuse
TEMPLATE = app
 

SOURCES += main.cpp \
        meinWidget.cpp \
        zeichenFeld.cpp

HEADERS  += meinWidget.h \
            zeichenFeld.h

CONFIG += c++11
