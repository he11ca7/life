QT += core gui widgets

TARGET = avtomat
TEMPLATE = app

INCLUDEPATH += \
    headers

SOURCES += \
    sources/main.cpp \
    sources/mainwindow.cpp \
    sources/clscellwidget.cpp \
    sources/clsworldwidget.cpp

HEADERS  += \
    headers/mainwindow.h \
    headers/clscellwidget.h \
    headers/clsworldwidget.h

RESOURCES += \
    res.qrc