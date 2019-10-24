#include "Components.h"
#include "GameObject.h"

namespace Oz
{
	cComponent::cComponent()
	{

	}

	void cComponent::onInit()
	{

	}

	void cComponent::onBegin()
	{

	}

	void cComponent::onUpdate()
	{

	}

	void cComponent::onDisplay()
	{

	}

	std::shared_ptr<cGameObject> cComponent::getGameObject()
	{
		return m_GameObject.lock();
	}

	std::shared_ptr<cCore> cComponent::getCore()
	{
		return getGameObject()->getCore();
	}
}