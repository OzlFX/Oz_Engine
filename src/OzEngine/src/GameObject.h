//Includes
#include "Exception.h"

#include <memory>
#include <list>

namespace Oz
{
	class cCore;
	class cTransform;

	class cGameObject
	{
		friend class cComponent;
		friend class cCore;

	private:

		//Vars
		std::weak_ptr<cGameObject> m_Self;
		std::weak_ptr<cCore> m_Core;
		std::weak_ptr<cTransform> m_Transform;

		std::list<std::shared_ptr<cComponent>> m_Components;

		//Functions
		void Update();
		void Display();

	public:
		cGameObject();

		//Get Component
		template <typename T> //Allow for passing of any object into the function
		//Allows the object to get a component object even if it isnt the component class
		std::shared_ptr<T> getComponent()
		{
			for (std::list<std::shared_ptr<cComponent>>::iterator it = m_Components.begin(); it != m_Components.end(); it++)
			{
				std::shared_ptr<T> component = std::dynamic_pointer_cast<T>(*it);

				if (component) //Check if of correct type
				{
					return component; //Return that type
				}
				else
				{
					throw Oz::Exception("Component does not exist!"); //Throw engine exception if the component cannot be found
				}
			}
		}

		//Add Component to the game object
		template <typename T, typename... A>
		std::shared_ptr<T> addComponent(A... args)
		{
			std::shared_ptr<T> component = std::make_shared<T>();

			if (component) //Check to see if the component is actually a component
			{
				//Add component to the list if the component is of type component
				component->m_GameObject = m_Self;
				component->m_Began = false;
				m_Components.push_back(component);
				component->onInit(args...);
				
				return component;
			}

			throw Oz::Exception("Added component isnt of type Component!"); //Thow engine exception if the added component isnt of the type component
		}

		std::shared_ptr<cTransform> getTransform(); //Get the object transform

		//Get Core
		std::shared_ptr<cCore> getCore();

		~cGameObject();
	};
}