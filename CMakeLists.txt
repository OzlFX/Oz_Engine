cmake_minimum_required(VERSION 2.6)
project(OzEngine)

#The Project Version Number
set (Oz_Engine_VERSION_MAJOR 1)
set (Oz_Engine_VERSION_MINOR 0)

include_directories(
	src
	contrib/msvc-windows-x86/SDL2/include
	contrib/msvc-windows-x86/glew/include
)

#Add the libraries to the project
add_library(OzEngine
	src/OzEngine/src/Core.h
	src/OzEngine/src/Core.cpp
	src/OzEngine/src/GameObject.h
	src/OzEngine/src/GameObject.cpp
	src/OzEngine/src/Components.h
	src/OzEngine/src/Components.cpp
)

#Add main executable
add_executable(Game
	src/Game/src/main.cpp
)

target_link_libraries(Game OzEngine)