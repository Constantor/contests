cmake_minimum_required(VERSION 3.25)
project(contests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(DEBUG false)

add_compile_options(-Wall -Wextra -Wextra -O2 -ffast-math)

if(UNIX AND DEBUG)
    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)
endif(UNIX AND DEBUG)

add_executable(kop kop.cpp)
add_executable(temp template.cpp)

add_executable(kop1 freeplay/kop/kop1.cpp)
add_executable(kop2 freeplay/kop/kop2.cpp)

add_executable(temp1 freeplay/temp/temp1.cpp)
add_executable(temp2 freeplay/temp/temp2.cpp)

add_executable(raw1 freeplay/raw/raw1.cpp)
add_executable(raw2 freeplay/raw/raw2.cpp)

add_executable(c_template_p1 contests/template/p1.cpp)
add_executable(c_template_p2 contests/template/p2.cpp)
add_executable(c_template_p3 contests/template/p3.cpp)
add_executable(c_template_p4 contests/template/p4.cpp)
add_executable(c_template_p5 contests/template/p5.cpp)
add_executable(c_template_p6 contests/template/p6.cpp)
add_executable(c_template_p7 contests/template/p7.cpp)
add_executable(c_template_p8 contests/template/p8.cpp)
