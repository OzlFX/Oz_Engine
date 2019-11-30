#include "Components.h"
#include "GameObject.h"
#include "Transform.h"
#include "MeshRend.h"
#include "Resources.h"
#include "Core.h"

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

	std::shared_ptr<cTransform> cComponent::getTransform()
	{
		return m_GameObject.lock()->getComponent<cTransform>();
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