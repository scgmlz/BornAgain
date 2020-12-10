#### Common infrastructure for standard tests.

Standard tests are run from
- `Tests/Functional/Core/Std`
- `Tests/Functional/Python/Std`
- `Tests/Functional/GUI/Std`

This directory provides some common code that it is compiled
separately in each of the above three directories.

`StandardTest.cpp`
: Provides TEST_F stances that define the BornAgain standard tests.

`Run.cpp`
: Defines a function `run`, which runs one standard simulation,
regardless whether it is in a Core, Py, or GUI test.

The specifities of Core vs Py vs GUI test are implemented in
a callback function `checkSimulation`, defined differently in
`Core/Std/Check.cpp`, `Python/..`, `GUI/..`.
