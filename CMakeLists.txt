cmake_minimum_required(VERSION 3.0)

project(outLineLib)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
include_directories(include)
aux_source_directory(src SRC_LIST)

add_compile_options(-std=c++11 -Wall -g)
find_library(Mysql mysqlclient)

add_executable(main ${SRC_LIST})

target_link_libraries (main ${Mysql})