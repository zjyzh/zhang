#-------------------------------------------------
#
# Project created by QtCreator 2019-07-03T09:30:10
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = projectjinbi
TEMPLATE = app
CONFIG += resources_big
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
        main.cpp \
        mainwindow.cpp \
    mypudhbutton.cpp \
    chooselevelscene.cpp \
    playsence.cpp \
    settingmenu.cpp \
    zooomb.cpp \
    selectbutton.cpp \
    PlantAndPosition.cpp \
    Selectplant.cpp \
    bullet.cpp \
    audioplayer.cpp

HEADERS += \
        mainwindow.h \
    mypudhbutton.h \
    chooselevelscene.h \
    playsence.h \
    settingmenu.h \
    zooomb.h \
    selectbutton.h \
    PlantAndPosition.h \
    SelectPlant.h \
    bullet.h \
    audioplayer.h

QT += multimedia multimediawidgets
FORMS +=


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    guan.qrc \
    youxi1.qrc \
    pvz.qrc \
    res.qrc
