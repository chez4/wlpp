# Copyright (C) 2020-2021 Max Burns
# See LICENSE for more information
# wlpp   - tests/CMakeLists.txt
# Author - chez4 10/11/2020

link_libraries(wlpp)

include_directories(wlpp PUBLIC
        "$<BUILD_INTERFACE:${wlpp_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

add_executable(test_window window.cpp)
set_target_properties(test_window PROPERTIES
        CXX_STANDARD 20
        CXX_EXTENSIONS OFF)
target_compile_options(test_window PRIVATE -Wextra -Wall -Wpedantic -march=native -flto)

add_test(window test_window)
