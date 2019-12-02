#include "Light.h"
#include "RenderSystem/ShaderProgram.h"

namespace Oz
{
	void cLight::setValue(std::weak_ptr<cMesh> _mesh)
	{
		//m_LightShader->setUniform("out_Model", _mesh.lock());
	}
}