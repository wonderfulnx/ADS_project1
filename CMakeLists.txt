cmake_minimum_required(VERSION 3.7)
project(pro_1_1)
find_package( OpenCV REQUIRED )

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp HogDescriptor.cpp HogDescriptor.h)
add_executable(pro_1_1 ${SOURCE_FILES})
target_link_libraries( pro_1_1 ${OpenCV_LIBS} )