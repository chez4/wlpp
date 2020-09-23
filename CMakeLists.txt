# wlpp Copyright 2020 Max Burns
# See LICENSE for more information.

cmake_minimum_required(VERSION 3.17)

project(wlpp VERSION 0.0.1 LANGUAGES CXX)

# Options ----------------------------------------------------------------------
option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(WLPP_INSTALL "Generate installation target" ON)

set(WLPP_LIB_NAME wlpp)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Select API -------------------------------------------------------------------
list(APPEND CMAKE_MODULE_PATH "${wlpp_SOURCE_DIR}/CMake")

if(UNIX)
    message(STATUS "Unix platform detected - using XCB")

    find_package(XCB REQUIRED)
    if (NOT XCB_FOUND)
        message(FATAL_ERROR "XCB library was not found")
    endif()
elseif(WIN32)
    message(STATUS "Windows platform detected - using Win32")

    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
else()
    message(FATAL_ERROR "No supported platform detected")
endif()

# Generate package files -------------------------------------------------------
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

set(WLPP_CONFIG_PATH "${CMAKE_INSTALL_LIBDIR}/cmake/wlpp")

configure_package_config_file(CMake/wlppConfig.cmake.in
        src/wlppConfig.cmake
        INSTALL_DESTINATION "${WLPP_CONFIG_PATH}"
        NO_CHECK_REQUIRED_COMPONENTS_MACRO)

write_basic_package_version_file(src/wlppConfigVersion.cmake
        VERSION ${wlpp_VERSION}
        COMPATIBILITY SameMajorVersion)

# Add subdirectory -------------------------------------------------------------
add_subdirectory(src)

# Install package and headers --------------------------------------------------
if(WLPP_INSTALL)
    install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    install(FILES "${CMAKE_BINARY_DIR}/src/wlppConfig.cmake"
            "${CMAKE_BINARY_DIR}/src/wlppConfigVersion.cmake"
            DESTINATION "${WLPP_CONFIG_PATH}")
    install(EXPORT wlppTargets FILE wlppTargets.cmake
            EXPORT_LINK_INTERFACE_LIBRARIES
            NAMESPACE wlpp::
            DESTINATION ${WLPP_CONFIG_PATH})
endif()
