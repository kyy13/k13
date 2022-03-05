# k13
# Kyle J Burgess

add_executable(
    test_byteswap
    src/main.cpp
)

target_include_directories(
    test_byteswap
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

IF (CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_options(
        test_byteswap
        PRIVATE
        -Wall
        -g
    )
ELSE()
    target_compile_options(
        test_byteswap
        PRIVATE
        -O3
    )
ENDIF()

target_link_libraries(
    test_byteswap
    ${PROJECT_NAME}
    -Wl,-allow-multiple-definition
)

add_test(
    NAME
    test_byteswap
    COMMAND
    test_byteswap
)

set_target_properties(
    test_byteswap
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS ON
)
