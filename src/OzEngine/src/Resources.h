#ifndef _CRESOURCES_H_
#define _CRESOURCES_H_

#include <memory>
#include <list>

#include "Mesh.h"
#include "Texture.h"
//#include "RenderTexture.h"

namespace Oz
{
	class cResource;

	class cResources
	{
		friend class cCore;

	private:

		std::list<std::shared_ptr<cResource>> m_Resources;

	public:

		template <typename T>
		std::shared_ptr<T> Load(std::string _path)
		{
			std::shared_ptr<T> resource; //Make a new resource

			resource = resource->Create(); //Create the resource
			resource->Load(_path); //Load a resource		

			m_Resources.push_back(resource); //add new resource to the list
			return resource;
		}

		template <typename T>
		std::shared_ptr<T> Load()
		{
			std::shared_ptr<T> resource; //Make a new resource

			resource = resource->Create(); //Create the resource	

			m_Resources.push_back(resource); //add new resource to the list
			return resource;
		}
	};
}

#endif