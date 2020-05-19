CONFIG -= qt

TEMPLATE = lib
DEFINES += CPPFAKER_LIBRARY

CONFIG += c++11

INCLUDEPATH += ./src /usr/local/include /usr/local/include/c++
INCLUDEPATH += src/includes

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../cpp-faker/src/faker/Base.cpp \
    ../cpp-fac/faker/JSON_Serializable.cpp \
    ../cpp-fasts/TestNumber.cpp \
    ../cpp-fasts/TestPhone.cpp \
    Faker.cpp \
    src/faker/Company.cpp \
    src/faker/Data.cpp \
    src/faker/ESports.cpp \
    src/faker/Name.cpp \
    src/faker/Number.cpp \
    src/faker/PhoneNumber.cpp \
    src/faker/StringVector.cpp \
    tests/TestCore.cpp \
    tests/TestName.cpp \
    tests/main-test.cpp

HEADERS += \
    ../cpp-fac/faker/Base.h \
    ../cpp-fac/faker/JSON_Serializable.h \
    ../cpp-fac/faker/json.hpp \
    ../cpp-fasts/TestNumber.h \
    ../cpp-fasts/TestPhone.h \
    ../cpp-fasts/UnitTesting.h \
    Faker.h \
    src/faker/Company.h \
    src/faker/Data.h \
    src/faker/ESports.h \
    src/faker/Name.h \
    src/faker/Number.h \
    src/faker/PhoneNumber.h \
    src/faker/StringVector.h \
    tests/TestCore.h \
    tests/TestName.h \
    tests/main-test.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
