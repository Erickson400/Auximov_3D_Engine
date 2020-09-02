#pragma once
#ifndef BUFFERVECTOR_H
#define BUFFERVECTOR_H

#include <iostream>
#include <SFML\Graphics.hpp>

namespace ax {
	class BufferVector {
	public:
		BufferVector(sf::Vector3f vert, sf::Texture& tex, float Resize, uint16_t id);
		BufferVector(sf::Vector3f vert, sf::Texture& tex, float Resize);

		float SpriteResize = 0.001;
		sf::Vector3f Position;
		sf::Texture* texture;
		uint16_t ID = 0; //0 means static and belongs to the world
	};
}
#endif // !BUFFERVECTOR_H



