######################################################################
# Automatically generated by qmake (3.0) Fri Jul 3 11:25:06 2015
######################################################################
TEMPLATE = app
TARGET = traff_sim
CONFIG += c++11
DEFINES += QTCTREATOR
LIBS += -lpthread -lboost_system -lboost_thread -lboost_regex

INCLUDEPATH += . test

SOURCES += \
    main.cpp \
#    test/lizard/lizard.cpp \
    src/street.cpp \
    src/car.cpp \
    src/utilities.cpp \
    src/base_event.cpp \
    src/joint.cpp \
    src/city.cpp \
    src/server.cpp

HEADERS += \
    inc/stdafx.hpp \
    inc/street.hpp \
    inc/car.hpp \
    inc/utilities.hpp \
    inc/base_event.hpp \
    inc/joint.hpp \
    test/lizard/lizard.hpp \
    test/lizard/stdafx.hpp \
    test/lizard/utilities.hpp \
    test/tests/basic/car_tester.hpp \
    test/tests/basic/joint_tester.hpp \
    test/tests/basic/street_tester.hpp \
    test/manifest.hpp \
    test/tests/basic/joint_kill_tester.hpp \
    test/tests/basic/joint_hold_tester.hpp \
    inc/city.hpp \
    inc/server.hpp \
    inc/http_request.hpp
