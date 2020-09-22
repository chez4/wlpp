# wlpp Copyright 2020 Max Burns
# See LICENSE for more information.

# Find XCB library using pkg-config --------------------------------------------
# Sets the following variables:
#   XCB_FOUND (if found)
#   XCB_LIBRARIES (if found)

find_package(PkgConfig)

pkg_check_modules(PKG_XCB QUIET xcb)

set(XCB_FOUND ${PKG_XCB_FOUND})
set(XCB_LIBRARIES ${PKG_XCB_LIBRARIES})
