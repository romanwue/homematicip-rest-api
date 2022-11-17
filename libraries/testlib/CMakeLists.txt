project(testlib)

set(SOURCES TestUtils.cpp)
set(HEADERS TestUtils.h)

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})

if(WIN32)
    add_definitions(/wd4996)
    target_compile_options(${PROJECT_NAME} PRIVATE "/WX") # msvs: treat warnings as errors
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/libraries/googletest/googletest/include
                                                   ${CMAKE_SOURCE_DIR}/libraries/googletest/googlemock/include)

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "Libraries")
