if(APPLE)
    set(ld_library_variable DYLD_LIBRARY_PATH)
else()
    set(ld_library_variable LD_LIBRARY_PATH)
endif()

# this script is a trick to print the message at the end of installation
if(NOT WIN32 AND NOT BORNAGAIN_APPLE_BUNDLE AND NOT BUILD_DEBIAN)
set(after_install_text "
Installation done. Please read below.
-------------------------------------------------------------------------------
To use BornAgain, add the directory ${CMAKE_INSTALL_PREFIX}/${destination_lib}
to your ${ld_library_variable} and PYTHONPATH.
You can do it by running the command 'source ${CMAKE_INSTALL_PREFIX}/${destination_bin}/thisbornagain.sh'
Just add this command into your .bashrc or .bash_profile file.
-------------------------------------------------------------------------------
")

install(CODE "MESSAGE(\"${after_install_text}\")")

endif()

# to show files in Qt creator
FILE(GLOB_RECURSE ScriptFiles "configurables/*.*")
add_custom_target(scripts SOURCES ${ScriptFiles})
