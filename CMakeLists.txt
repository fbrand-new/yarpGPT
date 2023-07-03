# Copyright (C) 2023 Fondazione Istituto Italiano di Tecnologia (IIT)  
# All Rights Reserved.
# Authors: Francesco Brand <francesco.brand@iit.it>

cmake_minimum_required(VERSION 3.5)

project(yarpGPT)

list(APPEND CMAKE_PREFIX_PATH "/vcpkg/installed/x64-linux")

message(${CMAKE_PREFIX_PATH})
find_package(YARP 3.8.0 REQUIRED COMPONENTS os)
find_package(CURL CONFIG REQUIRED)

add_subdirectory(src)
add_subdirectory(gui)

file(GLOB fakeDevice ${CMAKE_CURRENT_SOURCE_DIR}/app/conf/fakeLLMDevice.xml)
file(GLOB GPTDevice ${CMAKE_CURRENT_SOURCE_DIR}/app/conf/GPTDevice.xml)

yarp_install(FILES ${fakeDevice} DESTINATION ${YARP_CONTEXTS_INSTALL_DIR}/yarpGPT)
yarp_install(FILES ${GPTDevice} DESTINATION ${YARP_CONTEXTS_INSTALL_DIR}/yarpGPT)