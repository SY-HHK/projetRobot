cmake_minimum_required(VERSION 3.15)
project(code C)

set(CMAKE_C_STANDARD 99)

add_executable(code main.c)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(code ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} -lm )