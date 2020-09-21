cmake_minimum_required(VERSION 3.17)

project(wlpp VERSION 0.0.1 LANGUAGES CXX)

# Options ----------------------------------------------------------------------
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(WLPP_INSTALL "Generate installation target" ON)

set(WLPP_LIB_NAME wlpp)

# Select API -------------------------------------------------------------------
if(UNIX)
    message(STATUS "Unix platform detected - using XCB")
elseif(WIN32)
    message(STATUS "Windows platform detected - using Win32")
else()
    message(FATAL_ERROR "No supported platform detected")
endif()

# Generate package files -------------------------------------------------------
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

set(WLPP_CONFIG_PATH "${CMAKE_INSTALL_LIBDIR}/cmake/wlpp")

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/wlppConfig.cmake.in
        src/wlppConfig.cmake
        INSTALL_DESTINATION "${WLPP_CONFIG_PATH}"
        NO_CHECK_REQUIRED_COMPONENTS_MACRO) #NO_SET_AND_CHECK_MACRO

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
            NAMESPACE wlpp::
            DESTINATION ${WLPP_CONFIG_PATH})
endif()
