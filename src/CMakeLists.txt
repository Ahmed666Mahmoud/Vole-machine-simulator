cmake_minimum_required(VERSION 3.16)

project(VoleSimulator VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    MainWindow.cpp
    MainWindow.h
    MainWindow.ui
    Machine.cpp
    Machine.h
    CPU.cpp
    CPU.h
    ALU.cpp
    ALU.h
    Memory.cpp
    Memory.h
    RegisterBank.cpp
    RegisterBank.h
    Screen.cpp
    Screen.h
    ProgramLoader.cpp
    ProgramLoader.h
    MainMenu.cpp
    MainMenu.h
)

add_executable(VoleSimulator ${PROJECT_SOURCES})

target_link_libraries(VoleSimulator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
