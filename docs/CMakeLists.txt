# Copyright (C) 2020-2021 Max Burns
# See LICENSE for more information
# wlpp   - docs/CMakeLists.txt
# Author - chez4 14/10/2020

# Configure Doxyfile -----------------------------------------------------------
set(wlpp_DOXYGEN_INPUT "${wlpp_SOURCE_DIR}/include/wlpp")
configure_file(Doxyfile.in Doxyfile @ONLY)

# Doxygen build target ---------------------------------------------------------
add_custom_target(docs ALL "${DOXYGEN_EXECUTABLE}"
                  WORKING_DIRECTORY "${wlpp_BINARY_DIR}/docs"
                  COMMENT "Generating Doxygen documentation" VERBATIM)
