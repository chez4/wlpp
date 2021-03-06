# wlpp Copyright 2020 Max Burns
# See LICENSE for more information.

cmake_minimum_required(VERSION 3.17)

project(wlpp VERSION 0.0.1 LANGUAGES CXX)

# Options ----------------------------------------------------------------------
option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(wlpp_BUILD_DOCS "Build Doxygen documentation" ON)
option(wlpp_INSTALL "Generate installation target" ON)

set(wlpp_LIB_NAME wlpp)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

if (wlpp_BUILD_DOCS)
#    set(DOXYGEN_SKIP_DOT TRUE)
    find_package(Doxygen)
    if (NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen was not found")
    endif()
endif()

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

set(wlpp_CONFIG_PATH "${CMAKE_INSTALL_LIBDIR}/cmake/wlpp")

configure_package_config_file(CMake/wlppConfig.cmake.in
        src/wlppConfig.cmake
        INSTALL_DESTINATION "${wlpp_CONFIG_PATH}"
        NO_CHECK_REQUIRED_COMPONENTS_MACRO)

write_basic_package_version_file(src/wlppConfigVersion.cmake
        VERSION ${wlpp_VERSION}
        COMPATIBILITY SameMajorVersion)

# Add subdirectories -----------------------------------------------------------
add_subdirectory(src)

if(wlpp_BUILD_DOCS)
    add_subdirectory(docs)
endif()

# Install package and headers --------------------------------------------------
if(wlpp_INSTALL)
    install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
    install(FILES "${CMAKE_BINARY_DIR}/src/wlppConfig.cmake"
            "${CMAKE_BINARY_DIR}/src/wlppConfigVersion.cmake"
            DESTINATION "${wlpp_CONFIG_PATH}")
    install(EXPORT wlppTargets FILE wlppTargets.cmake
            EXPORT_LINK_INTERFACE_LIBRARIES
            NAMESPACE wlpp::
            DESTINATION ${wlpp_CONFIG_PATH})

    if(wlpp_BUILD_DOCS)
        install(DIRECTORY "${wlpp_BINARY_DIR}/docs/html"
                DESTINATION ${CMAKE_INSTALL_DOCDIR})
    endif()
endif()
