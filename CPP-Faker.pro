TEMPLATE = lib

CONFIG -= qt
CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17

DEFINES += CPPFAKER_LIBRARY

INCLUDEPATH += /usr/local/include
INCLUDEPATH += ./src
INCLUDEPATH += src/includes

LIBS += -lstdc++fs
QMAKE_LFLAGS += -lstdc++fs

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    src/faker/Base.cpp \
    src/faker/JSON_Serializable.cpp \
    src/faker/Address.cpp \
    src/faker/Company.cpp \
    src/faker/Data.cpp \
    src/faker/ESports.cpp \
    src/faker/Name.cpp \
    src/faker/Number.cpp \
    src/faker/PhoneNumber.cpp \
    src/faker/StringVector.cpp \
    tests/TestAddress.cpp \
    tests/TestCore.cpp \
    tests/TestName.cpp \
    tests/main-test.cpp

HEADERS += \
    src/faker/Address.h \
    src/faker/Base.h \
    src/faker/Company.h \
    src/faker/Data.h \
    src/faker/ESports.h \
    src/faker/Name.h \
    src/faker/Number.h \
    src/faker/PhoneNumber.h \
    src/faker/StringVector.h \
    tests/TestAddress.h \
    tests/TestCore.h \
    tests/TestName.h \
    tests/main-test.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
