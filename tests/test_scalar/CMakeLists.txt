# k13
# Kyle J Burgess

add_executable(
    test_scalar
    src/main.cpp
)

target_include_directories(
    test_scalar
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

IF (CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_options(
        test_scalar
        PRIVATE
        -Wall
        -g
    )
ELSE()
    target_compile_options(
        test_scalar
        PRIVATE
        -O3
    )
ENDIF()

target_link_libraries(
    test_scalar
    ${PROJECT_NAME}
    -Wl,-allow-multiple-definition
)

add_test(
    NAME
    test_scalar
    COMMAND
    test_scalar
)

set_target_properties(
    test_scalar
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS ON
)
