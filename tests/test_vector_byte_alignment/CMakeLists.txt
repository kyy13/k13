# k13
# Kyle J Burgess

add_executable(
    test_vector_byte_alignment
    src/main.cpp
)

target_include_directories(
    test_vector_byte_alignment
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

IF (CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_options(
        test_vector_byte_alignment
        PRIVATE
        -Wall
        -g
    )
ELSE()
    target_compile_options(
        test_vector_byte_alignment
        PRIVATE
        -O3
    )
ENDIF()

target_link_libraries(
    test_vector_byte_alignment
    ${PROJECT_NAME}
    -Wl,-allow-multiple-definition
)

add_test(
    NAME
    test_vector_byte_alignment
    COMMAND
    test_vector_byte_alignment
)

set_target_properties(
    test_vector_byte_alignment
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS ON
)
