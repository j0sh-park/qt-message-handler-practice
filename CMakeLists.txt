cmake_minimum_required(VERSION 3.10)
project(qt_practice)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(.)

set(CMAKE_PREFIX_PATH "C:\\Qt\\Qt5.8.0\\5.8\\mingw53_32\\bin")

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(qt_practice
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        message.cpp
        message.h
        messagehandler.cpp
        messagehandler.h
        messagepresenter.cpp
        messagepresenter.h
        messagesendtester.cpp
        messagesendtester.h
        qt_practice.pro)
target_link_libraries(qt_practice Qt5::Widgets)
