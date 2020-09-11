set(app ba3d_showcase)

find_package(Qt5Core     REQUIRED)
find_package(Qt5Gui      REQUIRED)
find_package(Qt5Widgets  REQUIRED)
find_package(OpenGL)

file(GLOB_RECURSE files *)
add_executable(${app} ${files})

target_link_libraries(${app}
  ba3d
  Qt5::Core Qt5::Gui Qt5::Widgets
  ${OPENGL_gl_LIBRARY}
)
