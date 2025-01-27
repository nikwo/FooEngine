cmake_minimum_required(VERSION 3.13)
project(FooEngine)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(third/glfw)
add_subdirectory(third/glm/glm)
add_subdirectory(third/assimp)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE FOOENGINE_SOURCES
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        ${CMAKE_SOURCE_DIR}/src/models_loader/*.cpp)
file(GLOB_RECURSE FOOENGINE_HEADERS
        ${CMAKE_SOURCE_DIR}/src/*.hpp
        ${CMAKE_SOURCE_DIR}/src/models_loader/*.hpp)

include_directories(third/glfw/include)
include_directories(third/glm/glm)
include_directories(third/assimp/include)
include_directories(third/stb)

add_library(FooEngineGraphics STATIC ${FOOENGINE_SOURCES} ${FOOENGINE_HEADERS})

target_link_libraries(FooEngineGraphics OpenGL::GL glfw GLEW assimp)

add_executable(main main.cpp)
target_link_libraries(main FooEngineGraphics)
