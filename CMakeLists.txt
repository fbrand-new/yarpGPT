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

file(GLOB conf ${CMAKE_CURRENT_SOURCE_DIR}/app/conf/yarpGPT.ini)

yarp_install(FILES ${conf} DESTINATION ${YARP_CONTEXTS_INSTALL_DIR}/yarpGPT)