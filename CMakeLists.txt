cmake_minimum_required(VERSION 3.5)
project(Game)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

#find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(freetype REQUIRED)

#find_package(glfw3 REQUIRED)

#pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp components/Button.cpp components/Button.h util/Shader.cpp util/Shader.h components/Rectangle.cpp components/Rectangle.h util/FontConfigs.cpp util/FontConfigs.h util/Character.h)
add_executable(Game ${SOURCE_FILES} components/Button.cpp components/Button.h util/Shader.cpp util/Shader.h components/Rectangle.cpp components/Rectangle.h util/FontConfigs.cpp util/FontConfigs.h)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR})
target_link_libraries(Game ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_glu_LIBRARY} ${OPENGL_gl_LIBRARY} opengl32 gdi32 glfw3 glu32 glew32 glm SOIL freetype)