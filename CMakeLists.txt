cmake_minimum_required(VERSION 3.0.0)
project(slow5_pod5_converter VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(slow5_pod5_converter
        src/main.c
        src/p2s_converter.c
        src/p2s_converter.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

include_directories(.)

set(main src/main.c)
set(p2s_converter src/p2s_converter.c)
