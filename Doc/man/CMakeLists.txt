set(AUTO_DIR ${CMAKE_SOURCE_DIR}/auto/Doc/man)
file(MAKE_DIRECTORY ${AUTO_DIR})

add_custom_target(
    man ALL
    DEPENDS ${AUTO_DIR}/bornagain.1
)

add_custom_command(
    OUTPUT ${AUTO_DIR}/bornagain.1
    COMMAND ${POD2MAN} -s 1 -c "BornAgain manual" ${CMAKE_CURRENT_SOURCE_DIR}/bornagain.pod ${AUTO_DIR}/bornagain.1
    DEPENDS bornagain.pod
)

install(FILES ${AUTO_DIR}/bornagain.1 DESTINATION ${CMAKE_INSTALL_PREFIX}/man/man1)
