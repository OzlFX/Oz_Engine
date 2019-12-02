#ifndef _CRESOURCES_H_
#define _CRESOURCES_H_

#include <memory>
#include <list>

#include "Mesh.h"
#include "RenderSystem/ShaderProgram.h"
#include "Texture.h"
#include "Material.h"

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
		std::shared_ptr<T> Load(std::string& _path)
		{
			std::shared_ptr<T> resource = std::make_shared<T>(); //Make a new thingy

			resource->Load(_path); //Load a resource

			m_Resources.push_back(resource); //Add Resource
			
			return resource;
		}

		template <typename T, typename... A>
		std::shared_ptr<T> Create(A... args)
		{
			for (std::list<std::shared_ptr<cResource>>::iterator it = m_Resources.begin(); it != m_Resources.end(); it++)
			{
				std::shared_ptr<T> resource = std::make_shared<T>(); //Make a new thingy

				resource->Create(args...); //Create the resource
			}
		}
	};
}

#endif