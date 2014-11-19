QSOLARSYSTEM_ROOT = $$PWD

QSOLARSYSTEM_BIN = $$QSOLARSYSTEM_ROOT/bin

QSOLARSYSTEM_INCLUDE = $$QSOLARSYSTEM_ROOT/common

QSOLARSYSTEM_OBJ_GUI = $$QSOLARSYSTEM_ROOT/obj_gui

QSOLARSYSTEM_MOC_GUI = $$QSOLARSYSTEM_ROOT/moc_gui

QSOLARSYSTEM_OBJ_TESTS = $$QSOLARSYSTEM_ROOT/obj_tests

QSOLARSYSTEM_MOC_TESTS = $$QSOLARSYSTEM_ROOT/moc_tests

QSOLARSYSTEM_SRC = $$QSOLARSYSTEM_ROOT/src

DESTDIR = $$QSOLARSYSTEM_BIN

QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Wmissing-declarations -Wredundant-decls -Wno-long-long -Wuninitialized
# -Wconversion -Winline

HEADERS += \
    $$PWD/common/point.hpp

SOURCES +=
