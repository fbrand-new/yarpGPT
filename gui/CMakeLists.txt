# Pick up our CMake scripts - they are all in the cmake subdirectory.
set(YARP_MODULE_DIR "/robotology/yarp/cmake")
list(APPEND CMAKE_MODULE_PATH ${YARP_MODULE_DIR})

# Find YCM
# This is required here, because YarpVersion uses GitInfo from YCM
set(YCM_REQUIRED_VERSION 0.15.1) # Used also by YarpFindDependencies
find_package(YCM ${YCM_REQUIRED_VERSION} REQUIRED)
find_package(YARP 3.8 COMPONENTS dev REQUIRED)

# Get the current YARP version.
# See cmake/YarpVersion.cmake.
include(YarpFindDependencies)
include(YarpInstallationHelpers)
include(YarpDeprecatedOption)
include(YarpUseQt5)

set(gui_QRC_FILES
  res.qrc
)

qt5_add_resources(gui_QRC_GEN_SRCS ${gui_QRC_FILES})

source_group(
  "Generated Files"
  FILES ${gui_QRC_GEN_SRCS}
)

add_executable(yarpGPT WIN32)

qtyarp_use_qml_plugin()

target_sources(yarpGPT 
  PRIVATE 
  main.cpp 
  ConversationModel.cpp 
  ${gui_UI_FILES}
  main.qml
  ${gui_QRC_GEN_SRCS}
  )
target_include_directories(yarpGPT PRIVATE "${CMAKE_CURRENT_BINARY_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/../src/c++/device")

target_link_libraries(yarpGPT
PRIVATE
  YARP::YARP_os
  YARP::YARP_init
  YARP::YARP_dev
  Qt5::Widgets
  Qt5::Gui
  Qt5::Qml
  Qt5::Quick
)

install(TARGETS yarpGPT DESTINATION bin)