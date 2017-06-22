cmake_minimum_required(VERSION 2.8)
PROJECT(MonocularVisualOdometry)

# Find the QtWidgets library
FIND_PACKAGE(Qt5Widgets)
FIND_PACKAGE( OpenCV REQUIRED )

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB SOURCES src/*.cpp)
file(GLOB SOURCESQT qt/mainQt.cpp)

add_library(qtwindow qt/mainwindow.cpp)
TARGET_LINK_LIBRARIES(qtwindow  Qt5::Widgets)

ADD_EXECUTABLE(visualodom WIN32 ${SOURCES})
ADD_EXECUTABLE(qtvisual WIN32 ${SOURCESQT})

qt5_use_modules(qtvisual Core Gui Widgets)
TARGET_LINK_LIBRARIES(visualodom ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(qtvisual qtwindow Qt5Widgets)
