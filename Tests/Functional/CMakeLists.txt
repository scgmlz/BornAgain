############################################################################
# Tests/Functional/CMakeLists.txt (called from top-level CMakeLists.txt)
############################################################################

include_directories(${CMAKE_SOURCE_DIR}/Tests/Functional/TestMachinery)

add_subdirectory(Core)
add_subdirectory(Fit)

if(BORNAGAIN_PYTHON)
    add_subdirectory(Python)
endif()

if(BORNAGAIN_GUI)
    add_subdirectory(GUI)
endif()
