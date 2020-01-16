#ifndef _CMATERIALATTRIB_H_
#define _CMATERIALATTRIB_H_

#include <memory>
#include <string>

namespace Oz
{
	class cTexture;

	class cMaterialAttribute
	{
	private:

		float m_Value;

	public:

		std::string m_Name;
		std::shared_ptr<cTexture> m_Texture;
		std::shared_ptr<cTexture> m_Normal;
		std::shared_ptr<cTexture> m_Roughness;
		std::shared_ptr<cTexture> m_Metallic;
		std::shared_ptr<cTexture> m_Disperse;
	};
}

#endif