#include <OzEngine/src/NonCopyable.h>

#include "Resource.h"

namespace Oz
{
	class cTexture : private cNonCopyable, public cResource
	{
	private:

		//Vars
		GLuint m_ID;
		bool m_Dirty;
		int m_Type;

		//Functions
		std::shared_ptr<cTexture> Create(unsigned int _width, unsigned int _height);
		std::shared_ptr<cTexture> Load(std::string _path);

	public:

		void setPixel(unsigned int _x, unsigned int _y, glm::vec3 _colour);
		void setPixel(unsigned int _x, unsigned int _y, glm::vec4 _colour);

		~cTexture();
	};
}