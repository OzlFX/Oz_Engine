#ifndef _CRESOURCES_H_
#define _CRESOURCES_H_

#include <memory>
#include <list>

#include "Mesh.h"
#include "RenderSystem/ShaderProgram.h"
#include "Texture.h"
#include "Material.h"
#include "Exception.h"

namespace Oz
{
	class cResource;

	class cResources
	{
		friend class cMesh;
		friend class cShaderProgram;
		friend class cTexture;
		friend class cMaterial;

	private:

		std::list<std::shared_ptr<cResource>> m_Resources;

	public:

		template <typename T>
		std::shared_ptr<T> Load(std::string _path)
		{
			std::shared_ptr<T> resource = std::make_shared<T>(); //Make a new thingy

			resource->Load(_path); //Load a resource
			
			return resource;
		}

		template <typename T>
		std::shared_ptr<T> Create()
		{
			//for (std::list<std::shared_ptr<cResource>>::iterator it = m_Resources.begin(); it != m_Resources.end(); it++)
			//{
				std::shared_ptr<T> resource = std::make_shared<T>(); //Make a new resource

				resource->Create(); //Create the resource

				m_Resources.push_back(resource); //Add resource
			//}
				return resource;
		}
	};
}

#endif