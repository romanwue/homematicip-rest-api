project(hmip)

add_library(${PROJECT_NAME} device.cpp
                            device.h
                            baseconnection.cpp
                            baseconnection.h
                            connection.cpp
                            connection.h
                            home.cpp
                            home.h
                            group.cpp
                            group.h
                            rule.cpp
                            rule.h
                            securityEvent.cpp
                            securityEvent.h)
set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "Libraries")

if(WIN32)
    target_compile_options(${PROJECT_NAME} PRIVATE "/WX") # msvs: treat warnings as errors
    target_link_libraries(${PROJECT_NAME} ws2_32)
endif()
