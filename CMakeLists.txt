cmake_minimum_required(VERSION 3.25)
project(contests)

set(CMAKE_CXX_STANDARD 20)

add_executable(template_kop.cpp template_kop.cpp)
add_executable(kop1 freeplay_kop/kop1.cpp)

add_executable(temp template.cpp)
add_executable(temp1 freeplay_template/temp1.cpp)

add_executable(freeplay1 freeplay/freeplay1.cpp)
