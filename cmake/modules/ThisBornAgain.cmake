# Install thisbornagain.sh.

if(WIN32)
    return()
endif()

install(FILES
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/thisbornagain.sh
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/thisbornagain.csh
    PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
    GROUP_EXECUTE GROUP_READ WORLD_EXECUTE WORLD_READ
    DESTINATION ${destination_libexec})

if(NOT BORNAGAIN_APPLE_BUNDLE AND NOT BUILD_DEBIAN)
    # Create bin directory for links.
    install(CODE "
        FILE(MAKE_DIRECTORY \"${CMAKE_INSTALL_PREFIX}/${destination_bin}\")
        "
        COMPONENT Runtime)
    # Make links.
    install(CODE "
    execute_process(COMMAND \${CMAKE_COMMAND} -E create_symlink
    \"../${destination_libexec}/thisbornagain.sh\" \"thisbornagain.sh\"
    WORKING_DIRECTORY \"${CMAKE_INSTALL_PREFIX}/${destination_bin}\")
    " COMPONENT Runtime)
    install(CODE "
    execute_process(COMMAND \${CMAKE_COMMAND} -E create_symlink
    \"../${destination_libexec}/thisbornagain.csh\" \"thisbornagain.csh\"
    WORKING_DIRECTORY \"${CMAKE_INSTALL_PREFIX}/${destination_bin}\")
    " COMPONENT Runtime)

else()
    install(FILES ${WRAP_DIR}/python/bornagain_python_install.py
        DESTINATION ${destination_libexec})
endif()
