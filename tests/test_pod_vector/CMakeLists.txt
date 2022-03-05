# k13
# Kyle J Burgess

add_executable(
    test_pod_vector
    src/main.cpp
)

target_include_directories(
    test_pod_vector
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

IF (CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_options(
        test_pod_vector
        PRIVATE
        -Wall
        -g
    )
ELSE()
    target_compile_options(
        test_pod_vector
        PRIVATE
        -O3
    )
ENDIF()

target_link_libraries(
    test_pod_vector
    ${PROJECT_NAME}
    -Wl,-allow-multiple-definition
)

add_test(
    NAME
    test_pod_vector
    COMMAND
    test_pod_vector
)

set_target_properties(
    test_pod_vector
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS ON
)
