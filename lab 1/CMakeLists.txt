cmake_minimum_required(VERSION 3.0.0)
project(LAB1)

find_package(OpenCV REQUIRED)
include_directories(${OPENCV_INCLUDE_DIRS})

add_executable(task1 task1/task1.cpp)
add_executable(task2 task2/task2.cpp)
add_executable(task3 task3/task3.cpp task3/removeColors.cpp)
add_executable(task4 task4/task4.cpp task4/oneColor.cpp)
add_executable(task5 task5/task5.cpp task5/black_white.cpp)

target_link_libraries(task1 ${OpenCV_LIBS})
target_link_libraries(task2 ${OpenCV_LIBS})
target_link_libraries(task3 ${OpenCV_LIBS})
target_link_libraries(task4 ${OpenCV_LIBS})
target_link_libraries(task5 ${OpenCV_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)