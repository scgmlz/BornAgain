############################################################################
# Core unit tests
############################################################################
set(test UnitTestCore)

set(libs BornAgainCore)

ADD_GTEST(${test} "Axes" ${libs} 0)
ADD_GTEST(${test} "Sample" ${libs} 0)
ADD_GTEST(${test} "Fresnel" ${libs} 0)
ADD_GTEST(${test} "Detector" ${libs} 0)
ADD_GTEST(${test} "ExportToPython" ${libs} 0)
ADD_GTEST(${test} "Parameters" ${libs} 0)
ADD_GTEST(${test} "DataStructure" ${libs} 0)
ADD_GTEST(${test} "Other" ${libs} 0)
ADD_GTEST(${test} "SimulationElement" ${libs} 0)
ADD_GTEST(${test} "Fitting" ${libs} 0)
ADD_GTEST(${test} "Numeric0" ${libs} 2)
ADD_GTEST(${test} "Numeric1" ${libs} 2)

