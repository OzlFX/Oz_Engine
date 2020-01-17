#ifndef _CMATERIALATTRIB_H_
#define _CMATERIALATTRIB_H_

#include <memory>
#include <string>

namespace Oz
{
	class cTexture;

	/* Contains all the necessary data for the material */
	class cMaterialAttribute
	{
	private:

		float m_Value;

	public:

		std::string m_Name; //Material's name
		std::shared_ptr<cTexture> m_Texture; //The main texture
		std::shared_ptr<cTexture> m_Normal; //The normal map
		std::shared_ptr<cTexture> m_Roughness; //The roughness map
		std::shared_ptr<cTexture> m_Metallic; //The metallic map
		std::shared_ptr<cTexture> m_Disperse; //The AO map
	};
}

#endif