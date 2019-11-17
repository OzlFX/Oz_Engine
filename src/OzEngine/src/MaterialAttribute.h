#include <memory>
#include <string>

namespace Oz
{
	class cMaterialAttribute
	{
		class cTexture;
	private:

		float m_Value;

	public:

		std::string m_Name;
		int m_Type;
		std::weak_ptr<cTexture> m_Texture;

	};
}