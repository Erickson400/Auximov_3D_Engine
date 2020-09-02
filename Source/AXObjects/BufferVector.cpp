#include "BufferVector.h"

namespace ax {
	BufferVector::BufferVector(sf::Vector3f vert, sf::Texture& tex, float Resize, uint16_t id) : ID(id), SpriteResize(Resize), texture(&tex), Position(vert) {};
	BufferVector::BufferVector(sf::Vector3f vert, sf::Texture& tex, float Resize) : SpriteResize(Resize), texture(&tex), Position(vert) {};

}
