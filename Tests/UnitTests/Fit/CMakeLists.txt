############################################################################
# CMakeLists.txt file for building and running unit tests
############################################################################

include(AddGTest)

include_directories(
    ../utilities
    ${BornAgainCore_INCLUDE_DIRS}
    ${BornAgainFit_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
    ${RootMinimizers_INCLUDE_DIRS}
    ${gtest_SOURCE_DIR}
    ${gtest_SOURCE_DIR}/include
    )
if(BORNAGAIN_OPENMPI)
    include_directories(${MPI_INCLUDE_PATH})
endif()

set(libs BornAgainCore BornAgainFit)
ADD_GTEST(Fit "0" "${libs}" 0)

