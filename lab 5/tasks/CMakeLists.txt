cmake_minimum_required(VERSION 3.0.0)
project(LAB5)

find_package(OpenCV REQUIRED)
include_directories(${OPENCV_INCLUDE_DIRS})

add_executable(task1 task1.cpp segmenter.cpp)
add_executable(task2 task2.cpp segmenter.cpp)
add_executable(task3 task3.cpp segmenter.cpp)

target_link_libraries(task1 ${OpenCV_LIBS})
target_link_libraries(task2 ${OpenCV_LIBS})
target_link_libraries(task3 ${OpenCV_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)