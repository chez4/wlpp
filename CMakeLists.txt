cmake_minimum_required(VERSION 3.18)

project(wlpp VERSION 0.0.1)

add_library(wlpp SHARED src/connection.cpp include/wlpp/connection.hpp src/screen.cpp include/wlpp/screen.hpp src/window.cpp include/wlpp/window.hpp)
target_link_libraries(wlpp PUBLIC xcb)

#add_library(wlpp_comp_flags INTERFACE)
#target_compile_features(wlpp_comp_flags INTERFACE cxx_std_20)
#set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU>")
#set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
#target_compile_options(wlpp_comp_flags INTERFACE
#                       "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wextra;-Wall;-Wpedantic;-march=native;-O3>>"
#                       "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>")
#
#target_link_libraries(wlpp INTERFACE wlpp_comp_flags)

install(TARGETS wlpp DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)

include(InstallRequiredSystemLibraries)
#set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${wlpp_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${wlpp_VERSION_MINOR}")
include(CPack)
