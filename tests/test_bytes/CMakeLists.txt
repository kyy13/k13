# k13
# Kyle J Burgess

add_executable(
    test_bytes
    src/main.cpp
)

target_include_directories(
    test_bytes
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

IF (CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_options(
        test_bytes
        PRIVATE
        -Wall
        -g
    )
ELSE()
    target_compile_options(
        test_bytes
        PRIVATE
        -O3
    )
ENDIF()

target_link_libraries(
    test_bytes
    ${PROJECT_NAME}
    -Wl,-allow-multiple-definition
)

add_test(
    NAME
    test_bytes
    COMMAND
    test_bytes
)

set_target_properties(
    test_bytes
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS ON
)
