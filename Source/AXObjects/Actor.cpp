#include "Actor.h"


namespace ax {
	Actor::Actor(sf::Vector3f pos, Model& modl, sf::Texture& tex, uint16_t id) : ID(id), texture(tex), Position(pos) {
		verts.clear();
		for (sf::Vector3f& vert : modl.verts) {
			verts.push_back(sf::Vector3f(vert.x + pos.x, -vert.y + pos.y, vert.z + pos.z));
		};
	}

	void Actor::Scale(float size) {
		for (sf::Vector3f& vect : verts) {
			vect = sf::Vector3f(vect.x * size, vect.y * size, vect.z * size);
		}
	}
	void Actor::setModel(Model& modl) {
		verts.clear();
		for (sf::Vector3f& vert : modl.verts) {
			verts.push_back(sf::Vector3f(vert.x + Position.x, -vert.y + Position.y, vert.z + Position.z));
		};
	}
	void Actor::pushToBuffer(std::vector<BufferVector>& buffer) {
		for (sf::Vector3f& vect : verts) {
			buffer.push_back(ax::BufferVector(vect, texture, SpriteResize));
		}
	}

}
