# # SPDX-FileCopyrightText: 2023-2023 Istituto Italiano di Tecnologia (IIT)
# # SPDX-License-Identifier: BSD-3-Clause

yarp_prepare_plugin(FakeLLMDevice
  CATEGORY device
  TYPE FakeLLMDevice
  INCLUDE FakeLLMDevice.hpp
  DEFAULT ON
)
yarp_add_plugin(yarp_FakeLLMDevice)

target_sources(yarp_FakeLLMDevice
PRIVATE
    FakeLLMDevice.cpp
    FakeLLMDevice.hpp
)

target_link_libraries(yarp_FakeLLMDevice
PRIVATE
    YARP::YARP_os
    YARP::YARP_dev
)

target_include_directories(yarp_FakeLLMDevice
PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/.."
  "${CMAKE_CURRENT_SOURCE_DIR}"
)

yarp_install(
TARGETS yarp_FakeLLMDevice
EXPORT yarp-device-gpt
COMPONENT yarp-device-gpt
LIBRARY DESTINATION ${YARP_DYNAMIC_PLUGINS_INSTALL_DIR}
ARCHIVE DESTINATION ${YARP_STATIC_PLUGINS_INSTALL_DIR}
YARP_INI DESTINATION ${YARP_PLUGIN_MANIFESTS_INSTALL_DIR}
)

set_property(TARGET yarp_FakeLLMDevice PROPERTY FOLDER "Plugins/Device")