Functional test to validate BornAgain in embedded Python interpreter.

Python script with BornAgain is executed inside Python interpreter embedded into C++ program.
Results of the simulation is retrieved as PyObject and converted to C++ counterpart.

Tests are executed automatically under the standard build step 'ctest'.
Can be run manually using ./bin/TestPyEmbedded
