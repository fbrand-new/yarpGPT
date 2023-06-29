# # SPDX-FileCopyrightText: 2006-2023 Istituto Italiano di Tecnologia (IIT)
# # SPDX-License-Identifier: BSD-3-Clause

yarp_prepare_plugin(GPT_nws_yarp
  CATEGORY device
  TYPE GPT_nws_yarp
  INCLUDE GPT_nws_yarp.h
  DEFAULT ON
)
yarp_add_plugin(GPT_nws_yarp)

target_sources(GPT_nws_yarp
PRIVATE
GPT_nws_yarp.cpp
GPT_nws_yarp.h
GPTServerImpl.cpp
GPTServerImpl.h
)

target_sources(GPT_nws_yarp
PRIVATE
$<TARGET_OBJECTS:IGPTMsgs>)

target_link_libraries(GPT_nws_yarp
PRIVATE
    YARP::YARP_os
    YARP::YARP_dev
)

target_include_directories(GPT_nws_yarp
PRIVATE 
"${CMAKE_CURRENT_SOURCE_DIR}"
"${CMAKE_CURRENT_SOURCE_DIR}/../thrift/generated/include"
"${CMAKE_CURRENT_SOURCE_DIR}/../device"
)

yarp_install(
TARGETS GPT_nws_yarp
EXPORT YARP_${YARP_PLUGIN_MASTER}
COMPONENT ${YARP_PLUGIN_MASTER}
LIBRARY DESTINATION ${YARP_DYNAMIC_PLUGINS_INSTALL_DIR}
ARCHIVE DESTINATION ${YARP_STATIC_PLUGINS_INSTALL_DIR}
YARP_INI DESTINATION ${YARP_PLUGIN_MANIFESTS_INSTALL_DIR}
)

set_property(TARGET GPT_nws_yarp PROPERTY FOLDER "Plugins/Device")