#pragma once
#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <SFML\Graphics.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <strstream>

namespace ax {
	class Model {
	public:
		Model(std::string filename);

		bool LoadModelFromFile(std::string filename);

		std::vector<sf::Vector3f> verts;
	};
}
#endif // !MODEL_H


