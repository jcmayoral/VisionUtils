set(PROJECT_NAME vision_utils)

PROJECT(${PROJECT_NAME})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
cmake_minimum_required(VERSION 2.8)

find_package( OpenCV REQUIRED )
file( GLOB SOURCE_FILES src/*.cpp)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories (${PROJECT_SOURCE_DIR} include)


file(GLOB_RECURSE hdrs "*.h") 

MESSAGE( STATUS "INCLUDE_DIRS: " ${OpenCV_LIBS} )
add_library(vision_utils SHARED ${SOURCE_FILES} ${hdrs})

target_link_libraries( vision_utils ${OpenCV_LIBS} )


MESSAGE( STATUS "INCLUDE_DIRS: " ${PROJECT_SOURCE_DIR} )
install (DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION include 
         FILES_MATCHING PATTERN "*.h")
install (
  TARGETS ${PROJECT_NAME} 
  ARCHIVE DESTINATION lib 
  LIBRARY DESTINATION lib 
  RUNTIME DESTINATION bin
) 

