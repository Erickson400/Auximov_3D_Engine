#include <iostream>
#ifndef GRAPHICS_HPP
#include <SFML\Graphics.hpp>
#endif
#include <string>
#include <vector>
#include <fstream>
#include <strstream>

class Camera {
public:
	Camera(sf::Vector3f Pos, sf::RenderWindow &win) : window(&win), Position(Pos) {};

	const float NEAR = 0.1, FAR = 50; // Clipping Planes
	sf::Vector3f Position = sf::Vector3f(0, 0, 0); 
	sf::Vector3f angle = sf::Vector3f(0, 0, 0);
	sf::RenderWindow *window;

	float Dist(float z1, float z2) {
		//TopLength / BottomLength = SpriteScale
		return abs(z1 - z2);
	}
};

class Model {
public:
	Model(std::string filename) {
		LoadModelFromFile(filename);
	}
	Model() {};
	std::vector<sf::Vector3f> verts;

	bool LoadModelFromFile(std::string filename) {
		verts.clear();
		std::ifstream file(filename);
		if (!file.is_open()) return false;
		
		while (!file.eof()) {
			char line[128];
			file.getline(line, 128);

			std::strstream s;
			s << line;

			char junk;
			if (line[0] == 'v'&& line[1] == ' ') {
				sf::Vector3f v;
				s >> junk >> v.x >> v.y >> v.z;
				verts.push_back(v);
			}
		}
		return true;
	}
};

class Actor {
public:
	Actor(sf::Vector3f pos, Model &modl, sf::Texture& tex): texture(tex), Position(pos) {
		verts.clear();
		for (sf::Vector3f &vert : modl.verts) {
			verts.push_back(sf::Vector3f(vert.x+pos.x, -vert.y+pos.y, vert.z+pos.z));
		};
	}

	std::vector<sf::Vector3f> verts;
	sf::Texture texture;
	sf::Vector3f Position;
	float SpriteResize = 0.001;

	void setModel(Model& modl) {
		verts.clear();
		for (sf::Vector3f& vert : modl.verts) {
			verts.push_back(sf::Vector3f(vert.x + Position.x, -vert.y + Position.y, vert.z + Position.z));
		};
	}

};

struct BufferVector {
	BufferVector(sf::Vector3f& vert, sf::Texture& tex, float Resize) : SpriteResize(Resize), texture(&tex), Position(vert) {};
	BufferVector(sf::Vector3f& vert, sf::Texture& tex) : texture(&tex), Position(vert) {};

	sf::Vector3f Position;
	sf::Texture *texture;
	float SpriteResize = 0.001;
};



