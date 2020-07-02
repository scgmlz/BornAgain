message(STATUS "Configuring BornAgainFit")

add_subdirectory(lib)
set(BornAgainFit_INCLUDE_DIRS ${BornAgainFit_INCLUDE_DIRS} PARENT_SCOPE)
set(BornAgainFit_LIBRARY ${BornAgainFit_LIBRARY} PARENT_SCOPE)

add_subdirectory(test)
