cmake_minimum_required(VERSION 2.6)
project(OzEngine)

#The Project Version Number
set (Oz_Engine_VERSION_MAJOR 1)
set (Oz_Engine_VERSION_MINOR 0)

include_directories(src)

#Add the libraries to the project
add_library(OzEngine
	src/OzEngine/src/OzEngine.h
	src/OzEngine/src/Core.h
	src/OzEngine/src/Core.cpp
	src/OzEngine/src/GameObject.h
	src/OzEngine/src/GameObject.cpp
	src/OzEngine/src/Components.h
	src/OzEngine/src/Components.cpp
	src/OzEngine/src/Exception.h
	src/OzEngine/src/Exception.cpp
	src/OzEngine/src/RenderSystem/VertexBuffer.h
	src/OzEngine/src/RenderSystem/VertexBuffer.cpp
	src/OzEngine/src/RenderSystem/VertexArray.h
	src/OzEngine/src/RenderSystem/VertexArray.cpp
	src/OzEngine/src/RenderSystem/ShaderProgram.h
	src/OzEngine/src/RenderSystem/ShaderProgram.cpp
)

link_directories(
	${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/glew/lib
	${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/lib
)

target_include_directories(OzEngine PUBLIC
	${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/glew/include
	${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/include
	${CMAKE_SOURCE_DIR}/contrib/glm
)

#Add main executable
add_executable(Game
	src/Game/src/main.cpp
)

target_link_libraries(Game OzEngine)