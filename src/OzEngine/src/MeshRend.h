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

	class cMeshRenderer : public cComponent
	{
	private:

		//Vars
		std::weak_ptr<cMesh> m_Mesh;
		std::shared_ptr<cMaterial> m_Material;
		std::shared_ptr<cTexture> m_Texture;
		std::shared_ptr<cRenderTexture> m_Default; //Default render texture

		std::shared_ptr<cShaderProgram> m_Shader; //Model shader
		std::shared_ptr<cShaderProgram> m_NullShader; //Null shader

		void onDisplay();

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