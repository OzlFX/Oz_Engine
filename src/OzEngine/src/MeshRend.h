#ifndef _CMESHRENDERER_H_
#define _CMESHRENDERER_H_

#include "Components.h"

#include <SDL2/SDL.h>

namespace Oz
{
	class cMesh;
	class cMaterial;
	class cTexture;
	class cShaderProgram;
	class cRenderTexture;

	/* Mesh Renderer Component, allows for the object to be rendered in 3D space.
	/* Takes a mesh and a texture or material */
	class cMeshRenderer : public cComponent
	{
	private:

		//Vars
		std::shared_ptr<cMesh> m_Mesh;
		std::shared_ptr<cMaterial> m_Material;
		std::shared_ptr<cTexture> m_Texture;
		std::list<std::shared_ptr<cGameObject>> m_Lights;
		//std::shared_ptr<cRenderTexture> m_Default; //Default render texture

		std::shared_ptr<cShaderProgram> m_Shader; //Model shader
		std::shared_ptr<cShaderProgram> m_LightShader; //Light Shader
		std::shared_ptr<cShaderProgram> m_DepthShader; //Light Shader
		std::shared_ptr<cShaderProgram> m_DepthQuad; //Light Shader
		//std::shared_ptr<cShaderProgram> m_NullShader; //Null shader
		
		//Functions
		void onDisplay(); //Render the object's with texture/material
		void postProcessing(); //Render post processing effects for the object

	public:

		void onBegin();
		void onInit();

		void setMesh(std::weak_ptr<cMesh> _mesh); //Set the mesh
		void setTexture(std::weak_ptr<cTexture> _texture); //Set the texture, use this if no material is provided
		void setMaterial(std::weak_ptr<cMaterial> _material); //Set the material

		std::shared_ptr<cMesh> getMesh(); //Get the mesh
		std::shared_ptr<cTexture> getTexture(); //Get texture, use this if no material is provided
		std::shared_ptr<cMaterial> getMaterial(); //Get material

		~cMeshRenderer();
	};
}

#endif