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
	private:

		std::list<std::shared_ptr<cResource>> m_Resources;

	public:

		template <typename T>
		std::shared_ptr<T> Load(std::string _path)
		{
			std::shared_ptr<T> resource = std::make_shared<T>(); //Make a new thingy

			resource->Create(); //Create the resource
			resource->Load(_path); //Load a resource
			
			return resource;
		}

	};
}

#endif