############################################################################
# CMakeLists.txt file for building and running unit tests
############################################################################

include(AddGTest)

# qtcreator prefers relative paths for project includes
include_directories(
    ../utilities
    ${BornAgainCore_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIR}
    ${GSL_INCLUDE_DIR}
    ${gtest_SOURCE_DIR}
    ${gtest_SOURCE_DIR}/include
    )
if(BORNAGAIN_OPENMPI)
    include_directories(${MPI_INCLUDE_PATH})
endif()

set(libs BornAgainCore)

ADD_GTEST(Core "Axes"        ${libs} 0)
ADD_GTEST(Core "Sample"        ${libs} 0)
ADD_GTEST(Core "Fresnel"        ${libs} 0)
ADD_GTEST(Core "Detector"        ${libs} 0)
ADD_GTEST(Core "Parameters"        ${libs} 0)
ADD_GTEST(Core "DataStructure"        ${libs} 0)
ADD_GTEST(Core "Other"        ${libs} 0)
ADD_GTEST(Core "Numeric0" ${libs} 1)
ADD_GTEST(Core "Numeric1" ${libs} 1)
