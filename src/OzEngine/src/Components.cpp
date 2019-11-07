#include "Components.h"
#include "GameObject.h"

namespace Oz
{
	cComponent::cComponent()
	{

	}

	//Init
	void cComponent::onInit()
	{

	}

	//Start
	void cComponent::onBegin()
	{

	}

	//Update
	void cComponent::onUpdate()
	{

	}

	//Display
	void cComponent::onDisplay()
	{

	}

	//Get the game object
	std::shared_ptr<cGameObject> cComponent::getGameObject()
	{
		return m_GameObject.lock();
	}

	//Get the core
	std::shared_ptr<cCore> cComponent::getCore()
	{
		return getGameObject()->getCore();
	}

	cComponent::~cComponent()
	{

	}
}