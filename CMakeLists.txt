cmake_minimum_required(VERSION 3.17)

project(window)

#agregar carpeta include
include_directories(include)

#archivos fuente
set(SOURCES
	src/utilities/glad/glad.c
)

#crear biblioteca
add_library(CustomLibrary ${SOURCES})

#crear un ejecutable
add_executable(${PROJECT_NAME} main.cpp)

#vincular biblioteca
target_link_libraries(${PROJECT_NAME} CustomLibrary)

#vincular GLFW
find_package(glfw3 REQUIRED)
target_link_libraries (${PROJECT_NAME} GL dl glfw)