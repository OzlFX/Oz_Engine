#ifndef _CTEXTURE_H_
#define _CTEXTURE_H_

#include <OzEngine/src/NonCopyable.h>

#include "Resource.h"

namespace Oz
{
	class cTexture : private cNonCopyable, public cResource
	{

		friend class cResources;
		friend class cRenderTexture;
		friend class cMaterial;

	private:

		//Vars
		
		bool m_Dirty;
		int m_Type;

		//Default size for texture
		unsigned int m_Width;
		unsigned int m_Height;

		glm::vec2 m_Size;

		unsigned int m_BorderSize; //The border size for the image

		int m_Channels;

		std::weak_ptr<cTexture> m_Self;

		//Functions
		std::shared_ptr<cTexture> Create(); //Create the texture
		std::shared_ptr<cTexture> Load(std::string _path); //Load the texture

	public:

		virtual void setSize(unsigned int _width, unsigned int _height); //Set the texture's size (cannot be negative)

		void setBorder(unsigned int _borderSize); //Set the desired border for the image

		glm::vec2 getSize();

		/* Probably wont ever use these */
		//void setPixel(unsigned int _x, unsigned int _y, glm::vec3 _colour);
		//void setPixel(unsigned int _x, unsigned int _y, glm::vec4 _colour);

		GLuint getID(); //Get the ID

		~cTexture();

	protected:

		GLuint m_ID;

	};
}

#endif