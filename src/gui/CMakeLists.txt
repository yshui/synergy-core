cmake_minimum_required (VERSION 3.4)

find_package (Qt5 COMPONENTS Widgets Network)
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTORCC ON)
set (CMAKE_AUTOUIC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)

file (GLOB LEGACY_GUI_SOURCE_FILES src/*.cpp src/*.h)
file (GLOB LEGACY_GUI_UI_FILES src/*.ui)

add_executable (synergyx
    ${LEGACY_GUI_SOURCE_FILES}
    ${LEGACY_GUI_UI_FILES}
    res/Synergy.qrc
)

include_directories (../lib/shared ./src)

qt5_use_modules (synergyx Widgets Network)

if (WIN32)
	set_target_properties (synergyx PROPERTIES LINK_FLAGS "/NODEFAULTLIB:LIBCMT")
endif()

target_link_libraries (synergyx shared)
