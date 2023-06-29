# # SPDX-FileCopyrightText: 2006-2023 Istituto Italiano di Tecnologia (IIT)
# # SPDX-License-Identifier: BSD-3-Clause

yarp_prepare_plugin(FakeGPTDevice
  CATEGORY device
  TYPE FakeGPTDevice
  INCLUDE FakeGPTDevice.hpp
  DEFAULT ON
)
yarp_add_plugin(yarp_FakeGPTDevice)

target_sources(yarp_FakeGPTDevice
PRIVATE
    FakeGPTDevice.cpp
    FakeGPTDevice.hpp
)

target_link_libraries(yarp_FakeGPTDevice
PRIVATE
    YARP::YARP_os
    YARP::YARP_dev
)

target_include_directories(yarp_FakeGPTDevice
PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/.."
  "${CMAKE_CURRENT_SOURCE_DIR}"
)

yarp_install(
TARGETS yarp_FakeGPTDevice
EXPORT yarp-device-gpt
COMPONENT yarp-device-gpt
LIBRARY DESTINATION ${YARP_DYNAMIC_PLUGINS_INSTALL_DIR}
ARCHIVE DESTINATION ${YARP_STATIC_PLUGINS_INSTALL_DIR}
YARP_INI DESTINATION ${YARP_PLUGIN_MANIFESTS_INSTALL_DIR}
)

set_property(TARGET yarp_FakeGPTDevice PROPERTY FOLDER "Plugins/Device")