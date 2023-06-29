# Thrift file generation
set(THRIFT_FILES IGPTMsgs.thrift)

yarp_idl_to_dir(INPUT_FILES ${THRIFT_FILES}
                OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/generated"
                SOURCES_VAR THRIFT_SOURCES
                HEADERS_VAR THRIFT_HEADERS
                INCLUDE_DIRS_VAR THRIFT_INCLUDE_DIRS)

message(STATUS "Thrift files: ${THRIFT_FILES}")
message(STATUS "Thrift headers: ${THRIFT_HEADERS}")
message(STATUS "Thrift sources: ${THRIFT_SOURCES}")
message(STATUS "Thrift include dirs: ${THRIFT_INCLUDE_DIRS}")

add_library(IGPTMsgs OBJECT)
target_sources(IGPTMsgs PRIVATE ${THRIFT_HEADERS}
                                            ${THRIFT_SOURCES}
                                            ${THRIFT_FILES})
target_include_directories(IGPTMsgs PUBLIC $<BUILD_INTERFACE:${THRIFT_INCLUDE_DIRS}>)

target_link_libraries(IGPTMsgs YARP::YARP_os)

set_property(TARGET IGPTMsgs PROPERTY FOLDER "Devices/Shared")

