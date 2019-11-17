#include <vector>
#include <OzEngine/src/NonCopyable.h>

#include "Resource.h"

namespace Oz
{
	class cFace;

	class cMesh : private cNonCopyable, public cResource
	{
	private:

		//Vars
		std::vector<cFace> m_Faces;
		bool m_Dirty;

		//Functions
		std::shared_ptr<cMesh> Create();
		std::shared_ptr<cMesh> Load(std::string _path);

	public:

		void addFace(cFace& _face);
		GLuint getID();

		~cMesh();
	};
}