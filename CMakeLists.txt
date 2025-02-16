# Copyright (C) 2025 Sergey Naumov <sergey@naumov.io>
# SPDX-License-Identifier: 0BSD

cmake_minimum_required(VERSION 3.15)

project(QtExt LANGUAGES CXX)

if(MSVC)
    cmake_policy(SET CMP0092 NEW) # Disable passing /W3 by default on MSVC
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

find_package(QT NAMES Qt6)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR}Loader)

if(NOT APPLE)
    set(CMAKE_INSTALL_RPATH $ORIGIN)
endif()

# QT_EXT_LIBRARY ---------------------------------------------------------------
include("cmake/QtExtConfigVersion.in")
set(QT_EXT_LIBRARY Qt${QT_VERSION_MAJOR}Ext)

add_library(${QT_EXT_LIBRARY} SHARED)

target_sources(${QT_EXT_LIBRARY}
    PRIVATE src/core/qtextglobal.h
            src/widgets/exthello.cpp
            src/widgets/exthello.h
            src/plugin.cpp
)

target_include_directories(${QT_EXT_LIBRARY}
    PRIVATE src/core
            src/widgets
)

set(QT_EXT_PUBLIC_HEADERS
    src/core/qtextglobal.h
    src/widgets/ExtHello
    src/widgets/exthello.h
)

set_target_properties(${QT_EXT_LIBRARY} PROPERTIES
    OUTPUT_NAME ${QT_EXT_LIBRARY}
    SOVERSION ${QT_VERSION_MAJOR}
    VERSION ${QT_EXT_VERSION}
    PUBLIC_HEADER "${QT_EXT_PUBLIC_HEADERS}"
)

target_link_libraries(${QT_EXT_LIBRARY}
    PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    PRIVATE Qt${QT_VERSION_MAJOR}Loader
)

target_compile_definitions(${QT_EXT_LIBRARY}
    PRIVATE QT_EXT_LIBRARY
)

include(GNUInstallDirs)
set(QT_EXT_INCLUDEDIR qt${QT_VERSION_MAJOR}/QtExt)
install(TARGETS ${QT_EXT_LIBRARY}
    EXPORT ${QT_EXT_LIBRARY}Targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            COMPONENT QtExt_Runtime
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT QtExt_Runtime
            NAMELINK_COMPONENT QtExt_Development
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT QtExt_Development
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${QT_EXT_INCLUDEDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${QT_EXT_INCLUDEDIR}
                  COMPONENT QtExt_Development
)

install(EXPORT ${QT_EXT_LIBRARY}Targets
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${QT_EXT_LIBRARY}
    FILE Qt${QT_VERSION_MAJOR}ExtTargets.cmake
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    cmake/QtExtConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${QT_EXT_LIBRARY}Config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${QT_EXT_LIBRARY}
    PATH_VARS CMAKE_INSTALL_LIBDIR CMAKE_INSTALL_INCLUDEDIR
)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${QT_EXT_LIBRARY}ConfigVersion.cmake
    VERSION ${QT_EXT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/${QT_EXT_LIBRARY}Config.cmake"
          "${CMAKE_CURRENT_BINARY_DIR}/${QT_EXT_LIBRARY}ConfigVersion.cmake"
          DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${QT_EXT_LIBRARY}"
)
