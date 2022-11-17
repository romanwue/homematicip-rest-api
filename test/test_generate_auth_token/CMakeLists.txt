project(test_generate_auth_token)

set(CMAKE_AUTOMOC TRUE)
set(CMAKE_AUTORCC TRUE)

set(SOURCES main.cpp)
set(HEADERS )

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "Unit Tests")

if(WIN32)
    target_compile_options(${PROJECT_NAME} PRIVATE "/WX") # msvs: treat warnings as errors
#    target_link_libraries(${PROJECT_NAME} ws2_32)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/libraries
                                                   ${CMAKE_SOURCE_DIR}/libraries/googletest/googletest/include
                                                   ${CMAKE_SOURCE_DIR}/libraries/googletest/googlemock/include)
target_link_libraries(${PROJECT_NAME} hmip gtest gtest_main testlib)
