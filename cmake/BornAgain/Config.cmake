###############################################################################
# BornAgain project configuration
###############################################################################

# -----------------------------------------------------------------------------
# configure files
# -----------------------------------------------------------------------------

configure_file(${CONFIGURABLES_DIR}/CTestCustom.cmake.in ${CMAKE_BINARY_DIR}/CTestCustom.cmake)

if (WIN32)
    # Necessary to provide correct slashes in BABuild.h
    file(TO_CMAKE_PATH ${Python3_EXECUTABLE} Python3_EXECUTABLE)
    file(TO_CMAKE_PATH ${Python3_STDLIB} Python3_STDLIB)
    file(TO_CMAKE_PATH ${Python3_STDLIB} Python3_STDLIB)
    file(TO_CMAKE_PATH ${Python3_INCLUDE_DIRS} Python3_INCLUDE_DIRS)
    file(TO_CMAKE_PATH ${Python3_NumPy_INCLUDE_DIRS} Python3_NumPy_INCLUDE_DIRS)
    file(TO_CMAKE_PATH ${Python3_SITELIB} Python3_SITELIB)
endif()

configure_file(${CONFIGURABLES_DIR}/BAVersion.h.in  ${BUILD_INC_DIR}/BAVersion.h @ONLY)
configure_file(${CONFIGURABLES_DIR}/BABuild.h.in  ${BUILD_INC_DIR}/BABuild.h @ONLY)
configure_file(${CONFIGURABLES_DIR}/BATesting.h.in  ${BUILD_INC_DIR}/BATesting.h @ONLY)
string(APPEND CMAKE_CXX_FLAGS " -I${BUILD_INC_DIR}")

configure_file(${CMAKE_SOURCE_DIR}/Examples/Python/utils/plot_int.py
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/plot_int.py COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/Examples/Python/utils/plot_diff_int.py
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/plot_diff_int.py COPYONLY)

# -----------------------------------------------------------------------------
# configure BornAgain launch scripts
# -----------------------------------------------------------------------------

set(this_bindir $BORNAGAINSYS/bin)
set(this_libdir $BORNAGAINSYS/lib/${destination_suffix})
configure_file(${CONFIGURABLES_DIR}/thisbornagain.sh.in
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/thisbornagain.sh @ONLY)
configure_file(${CONFIGURABLES_DIR}/thisbornagain.csh.in
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/thisbornagain.csh @ONLY)

# -----------------------------------------------------------------------------
# configure postinst and prerm for the debian package
# -----------------------------------------------------------------------------

if(BUILD_DEBIAN)
    set(CMAKE_INSTALL_PREFIX "/usr")
    configure_file(${CONFIGURABLES_DIR}/postinst.in ${BUILD_VAR_DIR}/postinst @ONLY)
    configure_file(${CONFIGURABLES_DIR}/prerm.in ${BUILD_VAR_DIR}/prerm @ONLY)
    set(CMAKE_INSTALL_RPATH \$ORIGIN/../;\$ORIGIN/../../lib/${destination_suffix})
endif(BUILD_DEBIAN)
