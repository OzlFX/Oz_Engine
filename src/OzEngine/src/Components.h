#ifndef _COMPONENTS_H_
#define _COMPONENTS_H_

//Includes
#include <memory>

namespace Oz
{
	class cGameObject;
	class cCore;

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
		cComponent();

		std::shared_ptr<cCore> getCore(); //Get the core
		std::shared_ptr<cGameObject> getGameObject(); //Get game object

		virtual ~cComponent();
	};
}

#endif // !_COMPONENTS_H_