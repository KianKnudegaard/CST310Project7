cmake_minimum_required(VERSION 3.20)
project(GLUTProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

# ── GLUT via vcpkg ────────────────────────────────────────────────────────────
find_package(GLUT REQUIRED)

function(add_glut_target TARGET_NAME SOURCE_FILE)
    add_executable(${TARGET_NAME} ${SOURCE_FILE})
    target_link_libraries(${TARGET_NAME} PRIVATE
        OpenGL::GL
        OpenGL::GLU
        GLUT::GLUT
    )
endfunction()

add_glut_target(CheckeredTriangles  src/CheckeredTriangles.cpp)
add_glut_target(ColorCubeFlyby      src/ColorCubeFlyby.cpp)
