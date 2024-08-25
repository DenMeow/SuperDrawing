#-------------------------------------------------
#
# Project created by QtCreator 2023-04-28T12:59:19
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sup_risov2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    chord.cpp \
    circle.cpp \
    ellips.cpp \
    line.cpp \
    m_arc.cpp \
    m_pie.cpp \
        main.cpp \
        mainwindow.cpp \
    color.cpp \
    mpen.cpp \
    dialog_style.cpp \
    dialog_points.cpp \
    my_widget.cpp \
    pixel.cpp \
    polygon.cpp \
    polyline.cpp \
    rect.cpp \
    tochka.cpp \
    triangle.cpp

HEADERS += \
    chord.h \
    circle.h \
    ellips.h \
    line.h \
    m_arc.h \
    m_pie.h \
        mainwindow.h \
    color.h \
    mpen.h \
    dialog_style.h \
    dialog_points.h \
    my_widget.h \
    pixel.h \
    polygon.h \
    polyline.h \
    rect.h \
    tochka.h \
    triangle.h

FORMS += \
        mainwindow.ui \
    dialog_style.ui \
    dialog_points.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource.qrc
