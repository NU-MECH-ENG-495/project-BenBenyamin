include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

add_executable(3D_TEST ${TEST_SOURCES})

enable_testing()

add_test(NAME 3D_TEST COMMAND 3D_TEST)

target_link_libraries(3D_TEST PUBLIC gtest gtest_main graphics)

target_compile_definitions(3D_TEST PRIVATE UNIT_TEST)

include(GoogleTest)
gtest_discover_tests(3D_TEST)
