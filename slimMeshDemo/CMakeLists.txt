cmake_minimum_required(VERSION 3.0)
project(main)
set(CMAKE_CXX_STANDARD 11)
link_directories("${CMAKE_CURRENT_SOURCE_DIR}/lib")
add_executable(main main.cpp)
target_link_libraries( main
                       PUBLIC)