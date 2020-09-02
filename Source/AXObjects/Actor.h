#pragma once
#ifndef ACTOR_H
#define ACTOR_H

#include <iostream>
#include <SFML\Graphics.hpp>
#include "Model.h"
#include "BufferVector.h"
#include <vector>

namespace ax {
	class Actor {
	public:
		Actor(sf::Vector3f pos, Model& modl, sf::Texture& tex, uint16_t id);

		void Scale(float size);
		void setModel(Model& modl);
		void pushToBuffer(std::vector<BufferVector>& buffer);

		std::vector<sf::Vector3f> verts;
		sf::Texture texture;
		sf::Vector3f Position;
		float SpriteResize = 0.001;
		uint16_t ID;
	};
}
#endif // !ACTOR_H



