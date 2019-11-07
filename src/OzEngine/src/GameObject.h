//Includes
#include "Exception.h"

#include <memory>
#include <list>

namespace Oz
{
	class cCore;
	class cComponent;

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
			}

			throw Oz::Exception("Component does not exist!"); //Throw engine exception if the component cannot be found
		}

		//Add Component to the game object
		template <typename T, typename... A>
		std::shared_ptr<T> addComponent(A... args)
		{
			std::shared_ptr<T> component = std::make_shared<T>();

			if (component = std::static_pointer_cast<cComponent>()) //Check to see if the component is actually a component
			{
				//Add component to the list if the component is of type component
				component->gameObject = m_Self;
				component->began = false;
				components.push_back(component);
				component->onInit(a);

				return component;
			}

			throw Oz::Exception("Component added isnt actually a component!"); //Thow engine exception if the added component isnt of the type component
		}

		//Get Core
		std::shared_ptr<cCore> getCore();

		~cGameObject();
	};
}