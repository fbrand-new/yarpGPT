add_executable(${PROJECT_NAME} main.cpp yarpGPT.h yarpGPT.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC "/liboai/liboai/include")
target_link_libraries(${PROJECT_NAME} PRIVATE oai ${YARP_LIBRARIES} CURL::libcurl)
link_directories("/liboai/liboai")

install(TARGETS ${PROJECT_NAME} DESTINATION bin)