cmake_minimum_required (VERSION 3.0)

find_package (Qt5 COMPONENTS Widgets Network LinguistTools REQUIRED)
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTORCC ON)
set (CMAKE_AUTOUIC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)

file (GLOB GUI_TRANSLATIONS res/lang/*.ts)
#qt5_add_translation (TRANSLATIONS ${GUI_TRANSLATIONS})

execute_process(
	COMMAND lrelease -silent ${GUI_TRANSLATIONS}
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	ERROR_QUIET
)

file (GLOB LEGACY_GUI_SOURCE_FILES src/*.cpp src/*.h)
file (GLOB LEGACY_GUI_UI_FILES src/*.ui)

if (APPLE)
	set (LEGACY_GUI_SOURCE_FILES ${LEGACY_GUI_SOURCE_FILES} src/OSXHelpers.h src/OSXHelpers.mm)
endif()

add_executable (synergygui WIN32
	${LEGACY_GUI_SOURCE_FILES}
	${LEGACY_GUI_UI_FILES}
	res/win/Synergy.rc
	res/Synergy.qrc
)

include_directories (./src)

qt5_use_modules (synergygui Widgets Network)

if (MSVC)
	set_target_properties (synergygui PROPERTIES LINK_FLAGS "/NODEFAULTLIB:LIBCMT")
endif()

if (APPLE)
	#set (MACOSX_BUNDLE_ICON_FILE Synergy.icns)
	#set (QSYNERGY_ICONS ${CMAKE_CURRENT_SOURCE_DIR}/res/mac/Synergy.icns)
	#set_source_files_properties ($QSYNERGY_ICONS} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
endif()
