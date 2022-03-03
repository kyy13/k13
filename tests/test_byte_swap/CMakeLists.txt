# k13
# Kyle J Burgess

add_executable(
    test_byte_swap
    src/main.cpp
)

target_include_directories(
    test_byte_swap
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

IF (CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_options(
        test_byte_swap
        PRIVATE
        -Wall
        -g
    )
ELSE()
    target_compile_options(
        test_byte_swap
        PRIVATE
        -O3
    )
ENDIF()

target_link_libraries(
    test_byte_swap
    ${PROJECT_NAME}
    -Wl,-allow-multiple-definition
)

add_test(
    NAME
    test_byte_swap
    COMMAND
    test_byte_swap
)

set_target_properties(
    test_byte_swap
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS ON
)
