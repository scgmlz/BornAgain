############################################################################
# Core unit tests
############################################################################

set(libs BornAgainCore)

ADD_GTEST(Core "Axes"        ${libs} 0)
ADD_GTEST(Core "Sample"        ${libs} 0)
ADD_GTEST(Core "Fresnel"        ${libs} 0)
ADD_GTEST(Core "Detector"        ${libs} 0)
ADD_GTEST(Core "ExportToPython"        ${libs} 0)
ADD_GTEST(Core "Parameters"        ${libs} 0)
ADD_GTEST(Core "DataStructure"        ${libs} 0)
ADD_GTEST(Core "Other"        ${libs} 0)
ADD_GTEST(Core "SimulationElement"        ${libs} 0)
ADD_GTEST(Core "Numeric0" ${libs} 2)
ADD_GTEST(Core "Numeric1" ${libs} 2)
