# Copyright (C) 2023 Fondazione Istituto Italiano di Tecnologia (IIT)  
# All Rights Reserved.
# Authors: Francesco Brand <francesco.brand@iit.it>

add_executable(${PROJECT_NAME} src/main.cpp src/yarpGPT.h src/yarpGPT.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(${PROJECT_NAME} PUBLIC "/liboai/liboai/include")
target_link_libraries(${PROJECT_NAME} PRIVATE oai ${YARP_LIBRARIES} CURL::libcurl)
link_directories("/liboai/liboai")

install(TARGETS ${PROJECT_NAME} DESTINATION bin)