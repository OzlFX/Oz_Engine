cmake_minimum_required(VERSION 2.6)
project(OzEngine)

#The Project Version Number
set (Oz_Engine_VERSION_MAJOR 1)
set (Oz_Engine_VERSION_MINOR 0)

include_directories(
	src
	contrib/glm
	contrib/msvc-windows-x86/glew/include
	contrib/msvc-windows-x86/SDL2/include
)

link_directories(
	${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/glew/lib
	${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/lib
)

#Add the libraries to the project
add_library(OzEngine
	src/OzEngine/src/NonCopyable.h
	src/OzEngine/src/OzEngine.h
	src/OzEngine/src/Core.h
	src/OzEngine/src/Core.cpp
	src/OzEngine/src/GameObject.h
	src/OzEngine/src/GameObject.cpp
	src/OzEngine/src/Components.h
	src/OzEngine/src/Components.cpp
	src/OzEngine/src/Exception.h
	src/OzEngine/src/Exception.cpp
	src/OzEngine/src/Transform.h
	src/OzEngine/src/Transform.cpp
	src/OzEngine/src/Camera.h
	src/OzEngine/src/Camera.cpp
	src/OzEngine/src/Light.h
	src/OzEngine/src/Light.cpp
	src/OzEngine/src/Mesh.h
	src/OzEngine/src/Mesh.cpp
	src/OzEngine/src/Texture.h
	src/OzEngine/src/Texture.cpp
	src/OzEngine/src/MeshRend.h
	src/OzEngine/src/MeshRend.cpp
	src/OzEngine/src/Resource.h
	src/OzEngine/src/Resources.h
	src/OzEngine/src/MaterialAttribute.h
	src/OzEngine/src/Material.h
	src/OzEngine/src/Material.cpp
	src/OzEngine/src/Context.h
	src/OzEngine/src/Context.cpp
	src/OzEngine/src/Environment.h
	src/OzEngine/src/Environment.cpp
	src/OzEngine/src/Keyboard.h
	src/OzEngine/src/Keyboard.cpp
	src/OzEngine/src/RenderSystem/VertexBuffer.h
	src/OzEngine/src/RenderSystem/VertexBuffer.cpp
	src/OzEngine/src/RenderSystem/VertexArray.h
	src/OzEngine/src/RenderSystem/VertexArray.cpp
	src/OzEngine/src/RenderSystem/ShaderProgram.h
	src/OzEngine/src/RenderSystem/ShaderProgram.cpp
	src/OzEngine/src/Utilities/Util.h
	src/OzEngine/src/Utilities/Util.cpp
)

target_link_libraries(OzEngine SDL2 opengl32 glew32)

#Add main executable
add_executable(Game
	src/Game/src/main.cpp
)

target_link_libraries(Game OzEngine)