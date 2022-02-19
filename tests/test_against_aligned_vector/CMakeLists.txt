# k13
# Kyle J Burgess

add_executable(
    test_against_aligned_vector
    src/main.cpp
)

target_include_directories(
    test_against_aligned_vector
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

IF (CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_options(
        test_against_aligned_vector
        PRIVATE
        -Wall
        -g
    )
ELSE()
    target_compile_options(
        test_against_aligned_vector
        PRIVATE
        -O3
    )
ENDIF()

target_link_libraries(
    test_against_aligned_vector
    ${PROJECT_NAME}
    -Wl,-allow-multiple-definition
)

add_test(
    NAME
    test_against_aligned_vector
    COMMAND
    test_against_aligned_vector
)

set_target_properties(
    test_against_aligned_vector
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS ON
)
