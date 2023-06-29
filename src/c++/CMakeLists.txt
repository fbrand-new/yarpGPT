# Copyright (C) 2023 Fondazione Istituto Italiano di Tecnologia (IIT)  
# All Rights Reserved.
# Authors: Francesco Brand <francesco.brand@iit.it>

# # SPDX-FileCopyrightText: 2006-2023 Istituto Italiano di Tecnologia (IIT)
# # SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.12)
project(yarp-device-gpt
        LANGUAGES CXX
        VERSION 0.1.0)

include(FeatureSummary)

find_package(YARP 3.8 COMPONENTS os dev idl_tools REQUIRED)
find_package(YCM 0.11 REQUIRED)

include(GNUInstallDirs)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(YARP_FORCE_DYNAMIC_PLUGINS TRUE CACHE INTERNAL "yarp-device-gpt is always built with dynamic plugins")
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "Build libraries as shared as opposed to static")

include(AddInstallRPATHSupport)
add_install_rpath_support(BIN_DIRS "${CMAKE_INSTALL_FULL_BINDIR}"
                            LIB_DIRS "${CMAKE_INSTALL_FULL_LIBDIR}"
                            INSTALL_NAME_DIR "${CMAKE_INSTALL_FULL_LIBDIR}"
                            USE_LINK_PATH)

set_property(GLOBAL PROPERTY USE_FOLDERS 1)

include(AddUninstallTarget)

#set(CMAKE_C_FLAGS "${YARP_C_FLAGS} ${CMAKE_C_FLAGS}")
#set(CMAKE_CXX_FLAGS "${YARP_CXX_FLAGS} ${CMAKE_CXX_FLAGS} -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")


yarp_configure_plugins_installation(yarp-device-gpt)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES)

add_subdirectory(module)
add_subdirectory(device)
add_subdirectory(thrift)
add_subdirectory(GPT_nws_yarp)
add_subdirectory(GPT_nwc_yarp)
add_subdirectory(example)