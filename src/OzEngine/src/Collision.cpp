#include "Collision.h"
#include "Components/ComponentIncludes.h"

#include <list>

namespace Oz
{
	/* BoxCollider Functions */
	void cBoxCollider::collideBox()
	{
		std::list<std::shared_ptr<cGameObject>> bces;

		bces = getCore()->getGameObjects();
		glm::vec3 np = getGameObject()->getTransform()->getPos() + m_Offset;

		for (std::list<std::shared_ptr<cGameObject>>::iterator it = bces.begin();
			it != bces.end(); it++)
		{
			if (*it == getGameObject())
			{
				continue;
			}

			std::shared_ptr<cBoxCollider> bc =
				(*it)->getComponent<cBoxCollider>();

			glm::vec3 sp = bc->getCollisionResponse(np, m_Size);
			np = sp;
			np = np - m_Offset;
			getGameObject()->getTransform()->setPos(np);
			m_LastPosition = np;
		}
	}

	bool cBoxCollider::isColliding(glm::vec3 _position, glm::vec3 _size)
	{
		glm::vec3 a = getGameObject()->getTransform()->getPos() + m_Offset;
		glm::vec3& as = this->m_Size;
		glm::vec3& b = _position;
		glm::vec3& bs = _size;

		if (a.x > b.x) // a right of b
		{
			if (a.x - as.x > b.x + bs.x) // left edge of a greater than right edge of b (not colliding)
			{
				return false;
			}
		}
		else
		{
			if (b.x - bs.x > a.x + as.x)
			{
				return false;
			}
		}

		if (a.z > b.z) // a front of b
		{
			if (a.z - as.z > b.z + bs.z) // back edge of a greater than front edge of b (not colliding)
			{
				return false;
			}
		}
		else
		{
			if (b.z - bs.z > a.z + as.z)
			{
				return false;
			}
		}

		if (a.y > b.y) // a above b
		{
			if (a.y - as.y > b.y + bs.y) // bottom edge of a greater than top edge of b (not colliding)
			{
				return false;
			}
		}
		else
		{
			if (b.y - bs.y > a.y + as.y)
			{
				return false;
			}
		}

		return true;
	}

	glm::vec3 cBoxCollider::getCollisionResponse(glm::vec3 _position, glm::vec3 _size)
	{
		float amount = 0.1f;
		float step = 0.1f;

		while (true)
		{
			if (!isColliding(_position, _size)) break;
			_position.x += amount;
			if (!isColliding(_position, _size)) break;
			_position.x -= amount;
			_position.x -= amount;
			if (!isColliding(_position, _size)) break;
			_position.x += amount;
			_position.z += amount;
			if (!isColliding(_position, _size)) break;
			_position.z -= amount;
			_position.z -= amount;
			if (!isColliding(_position, _size)) break;
			_position.z += amount;
			_position.y += amount;
			if (!isColliding(_position, _size)) break;
			_position.y -= amount;
			_position.y -= amount;
			if (!isColliding(_position, _size)) break;
			_position.y += amount;
			amount += step;
		}

		return _position;
	}

	void cBoxCollider::onInit(glm::vec3 _size, glm::vec3 _offset)
	{
		m_LastPosition = getGameObject()->getTransform()->getPos();
		m_Size = _size; //Set the box collider's size
		m_Offset = _offset; //Set the box collider's offset
	}

	void cBoxCollider::onUpdate()
	{
		collideBox();
	}

	/* MeshCollider Functions */
}