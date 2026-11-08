QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = VoleSimulator
TEMPLATE = app

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    Machine.cpp \
    CPU.cpp \
    ALU.cpp \
    Memory.cpp \
    RegisterBank.cpp \
    Screen.cpp \
    ProgramLoader.cpp \
    MainMenu.cpp

HEADERS += \
    MainWindow.h \
    Machine.h \
    CPU.h \
    ALU.h \
    Memory.h \
    RegisterBank.h \
    Screen.h \
    ProgramLoader.h \
    MainMenu.h

FORMS += \
    MainWindow.ui
