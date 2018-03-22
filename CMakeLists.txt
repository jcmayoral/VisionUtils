set(PROJECT_NAME vision_collision_detector)

PROJECT(${PROJECT_NAME})
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_AUTOMOC OFF)
set(CMAKE_AUTOUIC OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(OpenCV 3.2.0 REQUIRED PATHS "/home/jose/opencv-3.2.0-lib")
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5PrintSupport REQUIRED)
find_package(Qt5Widgets)

file(GLOB SOURCE_FILES src/*.cpp)
file(GLOB SOURCESQT *.cpp qcustomplot/*.cpp)
file(GLOB HEADERSQT *.h qcustomplot/*.h)
file(GLOB UIQT *.ui)

add_definitions( ${QT_DEFINITIONS} )
include_directories(include )#    ${catkin_INCLUDE_DIRS})

qt5_wrap_cpp(qt_vision_qt_sources  ${HEADERSQT})
qt5_wrap_ui(qt_vision_collision_detector_ui ${UIQT})

add_library(vision_collision_detector SHARED ${SOURCE_FILES})
add_executable(collision_detector WIN32 ${SOURCESQT} ${SOURCE_FILES} ${qt_vision_qt_sources} ${qt_vision_collision_detector_ui})

#MESSAGE( STATUS "INCLUDE_DIRS: " ${QT_LIBRARIES} )
target_link_libraries(vision_collision_detector ${OpenCV_LIBS} )#${catkin_LIBRARIES})
target_link_libraries(collision_detector ${OpenCV_LIBS} Qt5::Widgets Qt5::Core Qt5::Gui Qt5::PrintSupport)

install (DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION include)

install (
  TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)


install(
  TARGETS collision_detector
  RUNTIME DESTINATION bin
)
