# k13
# Kyle J Burgess

add_executable(
    test_event
    src/main.cpp
)

target_include_directories(
    test_event
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

IF (CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_options(
        test_event
        PRIVATE
        -Wall
        -g
    )
ELSE()
    target_compile_options(
        test_event
        PRIVATE
        -O3
    )
ENDIF()

target_link_libraries(
    test_event
    ${PROJECT_NAME}
    -Wl,-allow-multiple-definition
)

add_test(
    NAME
    test_event
    COMMAND
    test_event
)

set_target_properties(
    test_event
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS ON
)
