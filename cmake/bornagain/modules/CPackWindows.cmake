# BornAgain Windows packaging

set(SELECTED_PYTHON_VERSION "python${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}")

set(CPACK_PACKAGE_FILE_NAME
    "${CMAKE_PROJECT_NAME}-${BORNAGAIN_VERSION}-${SELECTED_PYTHON_VERSION}-${BORNAGAIN_ARCHITECTURE}")

set(CPACK_GENERATOR "NSIS")

set(CPACK_NSIS_INSTALL_ROOT "C:")
set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)

set(CPACK_NSIS_MENU_LINKS "bin\\\\BornAgain.exe" "BornAgain")


set(CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/GUI\\\\coregui\\\\images\\\\BornAgain.ico" )
set(CPACK_NSIS_MUI_ICON "${CMAKE_CURRENT_SOURCE_DIR}/GUI\\\\coregui\\\\images\\\\BornAgain.ico" )
set(CPACK_NSIS_MUI_UNIICON "${CMAKE_CURRENT_SOURCE_DIR}/GUI\\\\coregui\\\\images\\\\BornAgain.ico" )

set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "
  Push \\\"PYTHONPATH\\\"
  Push \\\"P\\\"
  Push \\\"HKCU\\\"
  Push \\\"$INSTDIR\\\\python\\\"
  Call EnvVarUpdate
  Pop  \\\$0

  CreateShortCut \\\"$DESKTOP\\\\BornAgain.lnk\\\" \\\"$INSTDIR\\\\bin\\\\BornAgain.exe\\\"
")

set(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "
  Push \\\"PYTHONPATH\\\"
  Push \\\"R\\\"
  Push \\\"HKCU\\\"
  Push \\\"$INSTDIR\\\\python\\\"
  Call un.EnvVarUpdate
  Pop  \\\$0

  RMDir /r \\\"$INSTDIR\\\\bin\\\"
  RMDir /r \\\"$INSTDIR\\\\python\\\"
  Delete \\\"$DESKTOP\\\\BornAgain.lnk\\\"
")

