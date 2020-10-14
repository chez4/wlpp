# wlpp Copyright 2020 Max Burns
# See LICENSE for more information.

# Configure Doxyfile -----------------------------------------------------------
set(wlpp_DOXYGEN_INPUT "${wlpp_SOURCE_DIR}/include/wlpp")
configure_file(Doxyfile.in Doxyfile @ONLY)

# Doxygen build target ---------------------------------------------------------
add_custom_target(docs ALL "${DOXYGEN_EXECUTABLE}"
                  WORKING_DIRECTORY "${wlpp_BINARY_DIR}/docs"
                  COMMENT "Generating Doxygen documentation" VERBATIM)
