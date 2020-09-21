# Add library ------------------------------------------------------------------
add_library(wlpp window.cpp)

add_library(wlpp_comp_flags INTERFACE)
target_compile_features(wlpp_comp_flags INTERFACE cxx_std_20)
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(wlpp_comp_flags INTERFACE
        "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-flto;-march=native;-O3;-std=c++20>>"
        "$<${msvc_cxx}:$<BUILD_INTERFACE:-O2;-std:c++20>>")
target_link_libraries(wlpp INTERFACE wlpp_comp_flags)

if(UNIX)
    target_sources(wlpp PRIVATE xcb/xcb_connection.cpp xcb/xcb_window.cpp
            xcb/xcb_screen.cpp)
elseif(WIN32)
    #target_sources(wlpp PRIVATE )
endif()

# Set properties ---------------------------------------------------------------
set_target_properties(wlpp PROPERTIES
        OUTPUT_NAME ${WLPP_LIB_NAME}
        VERSION ${wlpp_VERSION_MAJOR}.${wlpp_VERSION_MINOR}
        SOVERSION ${wlpp_VERSION_MAJOR}) #POSITION_INDEPENDENT_CODE ON

# Install library --------------------------------------------------------------
if(WLPP_INSTALL)
    install(TARGETS wlpp wlpp_comp_flags
            EXPORT wlppTargets
            RUNTIME DESTINATION "bin"
            ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
endif()
