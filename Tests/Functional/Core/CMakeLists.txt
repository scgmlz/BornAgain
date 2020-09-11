############################################################################
# Tests/Functional/Core/CMakeLists.txt
############################################################################

# add standard and special tests
add_subdirectory(Consistence)
add_subdirectory(CoreSpecial)
add_subdirectory(Fitting)
add_subdirectory(Std)

# build MPI test executable
if(BORNAGAIN_MPI)
    add_subdirectory(MPI)
endif()
