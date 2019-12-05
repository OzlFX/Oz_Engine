#ifndef _CMESHRENDERER_H_
#define _CMESHRENDERER_H_

#include "Components.h"

namespace Oz
{
	class cMesh;
	class cMaterial;
	class cTexture;
	class cShaderProgram;

	class cMeshRenderer : public cComponent
	{
	private:

		//Vars
		std::weak_ptr<cMesh> m_Mesh;
		std::shared_ptr<cMaterial> m_Material;
		std::shared_ptr<cTexture> m_Texture;

		void onDisplay();

	public:

		void onInit();

		void setMesh(std::weak_ptr<cMesh> _mesh); //Set the mesh
		void setMaterial(std::weak_ptr<cMaterial> _material); //Set the material

		std::shared_ptr<cMesh> getMesh(); //Get the mesh
		std::shared_ptr<cTexture> getTexture(); //Get texture
		std::shared_ptr<cMaterial> getMaterial(); //Get material

		~cMeshRenderer();
	};
}

#endif