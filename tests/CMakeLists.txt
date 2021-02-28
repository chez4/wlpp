# Copyright (C) 2020-2021 Max Burns
# See LICENSE for more information
# wlpp   - tests/CMakeLists.txt
# Author - chez4 10/11/2020

link_libraries(wlpp)

include_directories(wlpp PUBLIC
        "$<BUILD_INTERFACE:${wlpp_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

if(UNIX)
    add_executable(test_xcb xcb.cpp)
    set_target_properties(test_xcb PROPERTIES
            CXX_STANDARD 20
            CXX_EXTENSIONS OFF)
    target_compile_options(test_xcb PRIVATE -O3 -flto)
    target_link_options(test_xcb PRIVATE -O3 -flto)

    add_test(linux test_xcb)
elseif(WIN32)
    add_executable(test_win32 win32.cpp)
    set_target_properties(test_win32 PROPERTIES
            CXX_STANDARD 20
            CXX_EXTENSIONS OFF)
    target_compile_options(test_win32 PRIVATE -O3 -flto)
    target_link_options(test_win32 PRIVATE -O3 -flto -static-libstdc++ -static-libgcc -static)

    add_test(windows test_win32)
endif()
