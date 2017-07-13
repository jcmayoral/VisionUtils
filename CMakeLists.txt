SET(PROJECT_NAME vision_utils)

PROJECT(${PROJECT_NAME})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
cmake_minimum_required(VERSION 2.8)

find_package( OpenCV REQUIRED )

file( GLOB SOURCE_FILES src/*.cpp)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories ("${PROJECT_SOURCE_DIR}")

MESSAGE( STATUS "SOURCE_FILES:     " ${SOURCE_FILES} )

add_library(vision_utils ${SOURCE_FILES})

install (TARGETS vision_utils DESTINATION bin)
install (FILES vision_utils DESTINATION include)
