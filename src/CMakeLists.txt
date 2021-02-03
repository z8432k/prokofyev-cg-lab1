set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE  ON)

find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(GLUT REQUIRED)

include_directories(include)

add_library(pyramid OBJECT pyramid.cc)
target_link_libraries(pyramid PUBLIC ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})


add_executable(cube-cw cube-cw.cc)
target_link_libraries(cube-cw pyramid)
