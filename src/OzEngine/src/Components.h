#ifndef _COMPONENTS_H_
#define _COMPONENTS_H_

//Includes
#include <memory>

namespace Oz
{
	class cGameObject;
	class cCore;
	class cResources;
	
	/* Base component that holds basic data and functions that different component types will need */
	class cComponent
	{
		friend class cGameObject;

	private:

		std::weak_ptr<cGameObject> m_GameObject;
		bool m_Began;

		virtual void onInit();
		virtual void onBegin();
		virtual void onUpdate();
		virtual void onDisplay();

	public:

		std::shared_ptr<cCore> getCore(); //Get the core
		std::shared_ptr<cGameObject> getGameObject(); //Get game object
		std::shared_ptr<cResources> getResources(); //Get the resources

		virtual ~cComponent();
	};
}

#endif // !_COMPONENTS_H_