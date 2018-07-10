# BornAgain debian packaging
set(CPACK_GENERATOR "DEB")

# parameters to build a debian package
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Juan M. Carmona Loaiza <j.carmona.loaiza@fz-juelich.de>")

# Architecture: (mandatory)
IF(NOT CPACK_DEBIAN_PACKAGE_ARCHITECTURE)
    # There is no such thing as i686 architecture on debian, you should use i386 instead
    # $ dpkg --print-architecture
    FIND_PROGRAM(DPKG_CMD dpkg)
    IF(NOT DPKG_CMD)
        MESSAGE(STATUS "Can not find dpkg in your path, default to i386.")
        SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE i386)
    ENDIF(NOT DPKG_CMD)
    EXECUTE_PROCESS(COMMAND "${DPKG_CMD}" --print-architecture
        OUTPUT_VARIABLE CPACK_DEBIAN_PACKAGE_ARCHITECTURE
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
ENDIF(NOT CPACK_DEBIAN_PACKAGE_ARCHITECTURE)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_DEBIAN_PACKAGE_NAME "${CPACK_PACKAGE_NAME}")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
set(CPACK_STRIP_FILES "TRUE")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "build-essential, git, cmake(>=3.1), libgsl-dev(>=1.15), libboost-all-dev(>=1.48), libfftw3-dev(>=3.3.1), python3, python3-dev, python3-numpy, python3-matplotlib, libtiff5-dev(>=4.0.2), qt5-default(>=5.4), libqt5designercomponents5, qttools5-dev, libqt5svg5-dev")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION    "${CPACK_PACKAGE_DESCRIPTION}")
set(CPACK_DEBIAN_PACKAGE_VERSION ${BornAgain_VERSION_PATCH})
set(CPACK_PACKAGE_FILE_NAME "${CPACK_DEBIAN_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}-${CPACK_DEBIAN_PACKAGE_VERSION}_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")
set(CPACK_DEBIAN_PACKAGE_CONFLICTS "${CPACK_DEBIAN_PACKAGE_NAME}(<=${BORNAGAIN_VERSION})")

# set postinstall and preremove scripts for the debian package
set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${BUILD_VAR_DIR}/postinst;${BUILD_VAR_DIR}/prerm;")

# write copyright file
file(GENERATE OUTPUT "${CMAKE_BINARY_DIR}/copyright" INPUT "${CMAKE_SOURCE_DIR}/COPYING")

install(FILES "${CMAKE_BINARY_DIR}/copyright"
        DESTINATION "share/${destination_suffix}")


# write changelog file
execute_process(COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/CHANGELOG" "${CMAKE_BINARY_DIR}/changelog")
# execute_process(COMMAND gzip -9 "${CMAKE_BINARY_DIR}/changelog" OUTPUT_FILE "${CMAKE_BINARY_DIR}/changelog.gz")
execute_process(COMMAND gzip -9 "${CMAKE_BINARY_DIR}/changelog")
install(FILES "${CMAKE_BINARY_DIR}/changelog.gz" DESTINATION "share/${destination_suffix}")
