#ifndef _CLIGHT_H_
#define _CLIGHT_H_

#include "Components.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace Oz
{
	/*class cShaderProgram;

	class cShadowInfo
	{
	private:

		glm::mat4 m_Projection;
		float m_Bias;
		bool m_FlipFaces;

	public:

		cShadowInfo(const glm::mat4 _projection, float _bias, bool _flipFaces) :
			m_Projection(_projection),
			m_Bias(_bias),
			m_FlipFaces(_flipFaces) {}

		glm::mat4 GetProjection() { return m_Projection; }
		float GetBias() { return m_Bias; }
		bool GetFlipFaces() { return m_FlipFaces; }

	};*/

	class cLight : public cComponent
	{
	protected:

		glm::mat4 m_LightProjection, m_LightView;
		glm::mat4 m_LightSpaceMatrix;
		float m_NearPlane = 1.0f, m_FarPlane = 7.5f;

		glm::vec3 m_Colour;
		float m_Intensity;

		//std::shared_ptr<cShaderProgram> m_Shader;
		//std::shared_ptr<cShadowInfo> m_ShadowInfo;

		//void setShadowInfo(std::shared_ptr<cShadowInfo> _shadowInfo);

	public:

		void onInit(glm::vec3 _colour, float _intensity);
		void onBegin();

		float getNearPlane() { return m_NearPlane; }
		float getFarPlane() { return m_FarPlane; }
		//glm::mat4 getLightSpaceMatrix() { return m_LightSpaceMatrix; }
		glm::vec3 getColour() { return m_Colour; }
		//std::shared_ptr<cShadowInfo> getShadowInfo();

	};

	/*class cDirectionalLight : public cLight
	{
	private:

		std::shared_ptr<cShaderProgram> m_ShadowShader;

		glm::vec3 m_Emissive;
		glm::vec3 m_Ambient;
		glm::vec3 m_Specular;
		glm::vec3 m_Diffuse;

	public:

		void onInit(glm::vec3 _colour, float _intensity, glm::vec3 _emissive, 
			glm::vec3 _ambient, glm::vec3 _specular, glm::vec3 _diffuse);

		glm::vec3 getEmissive();
		glm::vec3 getAmbient();
		glm::vec3 getSpecular();
		glm::vec3 getDiffuse();

	};

	class cPointLight : public cLight
	{
	protected:

		glm::vec3 m_Emissive;
		glm::vec3 m_Ambient;
		glm::vec3 m_Specular;
		glm::vec3 m_Diffuse;

		float m_Constant;
		float m_Linear;
		float m_Quadratic;

		float m_Range;

	public:

		virtual void onInit(glm::vec3 _colour, float _intensity, glm::vec3 _emissive, 
			glm::vec3 _ambient, glm::vec3 _specular, glm::vec3 _diffuse, float _constant, float _linear, float _quadratic);

		float getConstant();
		float getLinear();
		float getQuadratic();
	};

	class cSpotLight : public cPointLight
	{
	private:

		float m_CutoffPoint;

	public:

		void onInit(glm::vec3 _colour, float _intensity, glm::vec3 _emissive,
			glm::vec3 _ambient, glm::vec3 _specular, glm::vec3 _diffuse, float _constant, 
			float _linear, float _quadratic, float _cutOffPoint);

	};*/
}

#endif