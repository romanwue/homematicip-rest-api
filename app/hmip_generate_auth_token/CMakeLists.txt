project(hmip_generate_auth_token)

add_executable(${PROJECT_NAME} main.cpp)
set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "Applications")

if(WIN32)
    target_compile_options(${PROJECT_NAME} PRIVATE "/WX") # msvs: treat warnings as errors
    target_link_libraries(${PROJECT_NAME} ws2_32)
endif()
