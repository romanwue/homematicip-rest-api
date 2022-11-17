add_subdirectory(hmip)
add_subdirectory(testlib)

set(GOOGLETEST_VERSION 1.11.0)
add_subdirectory(googletest)

set_property(TARGET gtest PROPERTY FOLDER "Unit Tests/Google Testing Framework")
set_property(TARGET gtest_main PROPERTY FOLDER "Unit Tests/Google Testing Framework")

set_property(TARGET gmock PROPERTY FOLDER "Unit Tests/Google Testing Framework")
set_property(TARGET gmock_main PROPERTY FOLDER "Unit Tests/Google Testing Framework")

if (WIN32)
    set(BUILD_SHARED_LIBS OFF)
    set(BUILD_OBJECT_LIBS OFF)
    set(JSONCPP_WITH_TESTS OFF)
    set(JSONCPP_WITH_POST_BUILD_UNITTEST OFF)
    add_subdirectory(jsoncpp)
endif()
