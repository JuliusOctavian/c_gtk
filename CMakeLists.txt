cmake_minimum_required(VERSION 3.21)
project(c_gui C)

set(CMAKE_C_STANDARD 99)

add_executable(c_gui main.c window.c window.h)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})

add_definitions(${GTK4_CFLAGS_OTHER})


target_link_libraries(c_gui ${GTK4_LIBRARIES})