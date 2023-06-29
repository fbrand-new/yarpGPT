add_executable(example example.cpp)

target_include_directories(example PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../device")
target_link_libraries(example PRIVATE ${YARP_LIBRARIES})