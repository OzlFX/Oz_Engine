#include "Components.h"
#include "Components/ComponentIncludes.h"
#include "Resources.h"
#include "Core.h"

namespace Oz
{
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

	//Get the gameobject the component is attached to
	std::shared_ptr<cGameObject> cComponent::getGameObject()
	{
		return m_GameObject.lock();
	}

	std::shared_ptr<cResources> cComponent::getResources()
	{
		return getGameObject()->getCore()->getResource();
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