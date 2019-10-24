#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

//Includes
#include "Components.h"

#include <memory>
#include <list>

#define ADDCOMPONENT \
	std::shared_ptr<T> rtn = std::make_shared<T>(); \
	rtn->gameObject = m_Self; \
	rtn->began = false; \
	components.push_back(rtn);

namespace Oz
{
	class cCore;

	class cGameObject
	{
		friend class cCore;

	private:

		//Vars
		std::weak_ptr<cGameObject> m_Self;
		std::weak_ptr<cCore> m_Core;

		std::list<std::shared_ptr<cComponent>> m_Components;

		//Functions
		void Update();
		void Display();

	public:
		cGameObject();

		//Get Component
		template <typename T>
		std::shared_ptr<T> getComponent()
		{
			for (size_t i = 0; i < m_Components.size(); i++)
			{
				std::shared_ptr<T> tst = std::dynamic_pointer_cast<T>(m_Components.at(i));

				if (tst) //Check if of correct type
				{
					return tst; //Return that type
				}
			}

			throw std::exception();
		}

		//Add Component functions
		template <typename T>
		std::shared_ptr<T> addComponent()
		{
			ADDCOMPONENT
			rtn->onInit();

			return rtn;
		}

		template <typename T, typename A>
		std::shared_ptr<T> addComponent(A a)
		{
			ADDCOMPONENT
				rtn->onInit(a);

			return rtn;
		}

		template <typename T, typename A, typename B>
		std::shared_ptr<T> addComponent(A a, B b)
		{
			ADDCOMPONENT
				rtn->onInit(a, b);

			return rtn;
		}

		//Get Core
		std::shared_ptr<cCore> getCore();

		~cGameObject();
	};
}

#endif