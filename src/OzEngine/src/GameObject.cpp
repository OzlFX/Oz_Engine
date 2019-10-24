#include "GameObject.h"

namespace Oz
{
	cGameObject::cGameObject()
	{

	}

	std::shared_ptr<cCore> cGameObject::getCore()
	{
		return m_Core.lock();
	}

	//Updates the components
	void cGameObject::Update()
	{
		for (std::list<std::shared_ptr<cComponent>>::iterator it = m_Components.begin(); it != m_Components.end(); it++)
		{
			//Check if it has not begun
			if (!(*it)->m_Began)
			{
				(*it)->onBegin(); //Run the beginning
				(*it)->m_Began = true; //It has begun!
			}

			(*it)->onUpdate(); //Update all components
		}
	}

	//Displays the components
	void cGameObject::Display()
	{
		for (std::list<std::shared_ptr<cComponent>>::iterator it = m_Components.begin(); it != m_Components.end(); it++)
		{
			(*it)->onDisplay(); //Display all components
		}
	}

	cGameObject::~cGameObject()
	{

	}
}