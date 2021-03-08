find_package(OpenGL REQUIRED)
find_package(Qt5 COMPONENTS Core Gui Widgets Designer PrintSupport Network Svg OpenGL REQUIRED)

message(STATUS "Found Qt5 version ${Qt5Widgets_VERSION}")

if(${Qt5Core_VERSION} VERSION_LESS "5.5.1")
    # required for OpenGL, hence for ba3d
    message (FATAL_ERROR "Qt 5.5.1+ is required, have ${Qt5Core_VERSION_STRING}")
endif()

get_target_property(Qt5Widgets_location Qt5::Widgets LOCATION_Release)
message(STATUS "  ${Qt5Widgets_LIBRARIES} ${Qt5Widgets_location}")
get_target_property(Qt5Core_location Qt5::Core LOCATION_Release)
message(STATUS "  ${Qt5Core_LIBRARIES} ${Qt5Core_location}")
get_target_property(Qt5Gui_location Qt5::Gui LOCATION_Release)
message(STATUS "  ${Qt5Gui_LIBRARIES} ${Qt5Gui_location}")
get_target_property(Qt5OpenGL_location Qt5::OpenGL LOCATION_Release)
message(STATUS "  ${Qt5OpenGL_LIBRARIES} ${Qt5OpenGL_location}")

message(STATUS "  Includes: ${Qt5Widgets_INCLUDE_DIRS}")

# suppress qDebug() output for release build
if(CMAKE_BUILD_TYPE STREQUAL Release)
    add_definitions(-DQT_NO_DEBUG_OUTPUT)
endif()
