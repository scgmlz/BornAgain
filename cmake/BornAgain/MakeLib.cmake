# Configure one component library.

function(MakeLib name lib tmpdir)

    if(BORNAGAIN_PYTHON)
        list(APPEND source_files ${AUTO_DIR}/lib${lib}_wrap.cpp)
    endif()

    add_library(${lib} SHARED ${source_files})
    set_target_properties(${lib} PROPERTIES PREFIX ${libprefix} SUFFIX ${libsuffix})
    if(APPLE AND BORNAGAIN_APPLE_BUNDLE)
        set(link_flags "-Wl,-rpath,@loader_path/../../Frameworks")
        set_target_properties(${lib} PROPERTIES LINK_FLAGS ${link_flags})
    endif()

    set(${lib}_LIBRARY_TYPE SHARED)

    if(BORNAGAIN_PYTHON)
        SwigLib(${name} ${lib} ${tmpdir})
    endif(BORNAGAIN_PYTHON)

    install(TARGETS ${lib} DESTINATION ${destination_lib} COMPONENT Libraries)
    foreach(file ${include_files})
        get_filename_component(dir ${file} DIRECTORY)
        install(FILES ${file} DESTINATION ${destination_include}/${name}/${dir})
    endforeach()

endfunction()
