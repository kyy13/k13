# k13
# Kyle J Burgess

cmake_minimum_required(VERSION 3.7)
project(k13)

option(BUILD_TESTS "build tests?" ON)

# library
add_library(
    ${PROJECT_NAME} STATIC
    src/color.cpp
    src/thread_pool.cpp
)

# includes
target_include_directories(
    ${PROJECT_NAME} PUBLIC
    include
)

# linker options
target_link_options(
    ${PROJECT_NAME} PRIVATE
    -lwinpthread
)

# c++ version
set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS ON
)

IF(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
ENDIF()
