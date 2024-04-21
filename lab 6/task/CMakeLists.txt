cmake_minimum_required(VERSION 3.0.0)
project(LAB6)

find_package(OpenCV REQUIRED)
include_directories(${OPENCV_INCLUDE_DIRS})

add_executable(task task.cpp imageMatcher.cpp)

target_link_libraries(task ${OpenCV_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)