# wlpp Copyright 2020 Max Burns
# See LICENSE for more information.

# Add library ------------------------------------------------------------------
add_library(wlpp window.cpp window_api_error.cpp)

target_include_directories(wlpp PUBLIC
        "$<BUILD_INTERFACE:${wlpp_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")
target_include_directories(wlpp PRIVATE
        "${wlpp_SOURCE_DIR}/src"
        "${wlpp_BINARY_DIR}/src"
        ${wlpp_INCLUDE_DIRS})

# Choose platform-specific sources and libraries -------------------------------
if(UNIX)
    target_sources(wlpp PRIVATE xcb/xcb_connection.cpp xcb/xcb_window.cpp
            xcb/xcb_screen.cpp)

    target_link_libraries(wlpp PUBLIC ${PKG_XCB_LIBRARIES})
elseif(WIN32)
    target_sources(wlpp PRIVATE win32/win32_window.cpp)

    target_link_libraries(wlpp PRIVATE Threads::Threads)
endif()

# Set properties ---------------------------------------------------------------
set_target_properties(wlpp PROPERTIES
        CXX_STANDARD 20
        CXX_EXTENSIONS OFF
        OUTPUT_NAME ${WLPP_LIB_NAME}
        VERSION ${wlpp_VERSION_MAJOR}.${wlpp_VERSION_MINOR}
        SOVERSION ${wlpp_VERSION_MAJOR})

# Install library --------------------------------------------------------------
if(WLPP_INSTALL)
    install(TARGETS wlpp
            EXPORT wlppTargets
            RUNTIME DESTINATION "bin"
            ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
endif()
