project(k13)

# library
add_library(
    ${PROJECT_NAME} STATIC
    src/color.cpp
    src/thread_pool.cpp
)

# test exe
add_executable(
    TEST
    src/main.cpp
)

# includes
target_include_directories(
    ${PROJECT_NAME} PUBLIC
    include
)

target_include_directories(
    TEST PUBLIC
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

# compiler flags
IF (CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_options(TEST PUBLIC -Wall -g)
ELSE()
    add_compile_options(TEST PUBLIC -O3)
ENDIF()

#linker flags

set(
    CMAKE_CXX_STANDARD_LIBRARIES
    "-static-libgcc -static-libstdc++ ${CMAKE_CXX_STANDARD_LIBRARIES}"
)

set(
    CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -Wl,--no-whole-archive"
)

target_link_libraries(
    TEST
    k13
)