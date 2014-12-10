#-------------------------------------------------
#
# Project created by QtCreator 2014-11-19T09:46:26
#
#-------------------------------------------------

include(../QSolarSystem.pri)

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QSolarSystem
TEMPLATE = app

CONFIG += debug_and_release

INCLUDEPATH += ../common/

LIBS += -lboost_system$$BOOST_SUFFIX -lboost_filesystem$$BOOST_SUFFIX

SOURCES += main.cpp\
        mainwindow.cpp \
    ../common/body.cpp \
    ../common/bodyparser.cpp \
    ../common/solarsystem.cpp \
    ../common/utils/string.cpp \
    screen.cpp \
    commanddock.cpp \
#    ../common/updater/updaterboostwithunits.cpp \
    ../common/updater/updaterboostnounits.cpp \
    ../common/updater/iupdater.cpp

HEADERS  += mainwindow.hpp \
    ../common/body.hpp \
    ../common/bodyparser.hpp \
    ../common/solarsystem.hpp \
    ../common/utils/deep_ptr.hpp \
    ../common/utils/make_unique.hpp \
    ../common/utils/namespace_utils.hpp \
    ../common/utils/noncopiable.hpp \
    ../common/utils/noninstantiable.hpp \
    ../common/utils/pimpl.hpp \
    ../common/utils/string.hpp \
    ../common/point.hpp \
    screen.hpp \
    commanddock.hpp \
#    ../common/updater/updaterboostwithunits.hpp \
    ../common/updater/updaterboostnounits.hpp \
    ../common/updater/iupdater.hpp \
    ../common/updater/crtp_updater.hpp \
    ../common/utils/factory.hpp \
    ../common/utils/defaultfactoryerrorpolicy.hpp \
    ../common/utils/singleton.hpp \
    ../common/updater/updaterfactory.hpp \
    ../common/updater/parametertrait.hpp
