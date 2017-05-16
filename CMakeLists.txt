cmake_minimum_required(VERSION 3.5)
project(Game)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
find_package(glm REQUIRED)
find_package(freetype REQUIRED)

find_package(glfw3 3.2 REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})

pkg_search_module(GLEW REQUIRED glew)
include_directories(${GLEW_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp components/Button.cpp components/Button.h util/Shader.cpp util/Shader.h
        components/Rectangle.cpp components/Rectangle.h util/FontConfigs.cpp util/FontConfigs.h util/Character.h
        components/TextDraw.cpp components/TextDraw.h components/InputText.cpp
        components/InputText.h components/GUI/Menu.cpp components/GUI/Menu.h components/Square.cpp components/Square.h
        components/Cube.cpp components/Cube.h util/Camera.cpp util/Camera.h components/Player.cpp components/Player.h
        entities/Entity.cpp entities/Entity.h util/Maths.cpp util/Maths.h util/ProjectionMatrix.cpp
        util/ProjectionMatrix.h util/io/Mouse.cpp util/io/Mouse.h util/ObjLoader.cpp util/ObjLoader.h entities/RawModel.cpp
        entities/RawModel.h entities/Loader.cpp entities/Loader.h components/ObjModel.cpp components/ObjModel.h
        )
add_executable(Game ${SOURCE_FILES})

include_directories(${GLEW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
target_link_libraries(Game ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_gl_LIBRARY} SOIL freetype
        ${FREETYPE_LIBRARIES} ${GLUT_LIBRARY} opengl32 gdi32)
