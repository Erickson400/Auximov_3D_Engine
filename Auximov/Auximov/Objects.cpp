#include <iostream>
#ifndef GRAPHICS_HPP
#include <SFML\Graphics.hpp>
#endif
#include <string>
#include <vector>
#include <fstream>
#include <strstream>

struct Camera {
public:
	Camera(sf::Vector3f Pos, sf::RenderWindow &win) : window(&win), Position(Pos) {};
	Camera(){};
	~Camera() { delete window; };

	const float NEAR = 0.1, FAR = 100; // Clipping Planes
	sf::Vector3f Position = sf::Vector3f(0, 0, 0); 
	sf::Vector3f angle = sf::Vector3f(0, 0, 0);
	sf::RenderWindow *window = new sf::RenderWindow();

	float Dist(float z1, float z2) {
		//TopLength / BottomLength = SpriteScale
		return abs(z1 - z2);
	}
};

class Model {
public:
	Model(std::string filename) {
		std::cout << "Model Loaded" << std::endl;
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
	Actor(sf::Vector3f pos, Model &modl, sf::Texture& tex): texture(tex), Position(pos), model(modl) {
		std::cout << "Actor Created" << std::endl;
		verts.clear();
		for (sf::Vector3f &vert : model.verts) {
			verts.push_back(sf::Vector3f(vert.x, -vert.y, vert.z));
		};
	}
	Actor(){};

	std::vector<sf::Vector3f> verts;
	sf::Texture texture = sf::Texture();
	sf::Vector3f Position;
	Model model;

	void setModel(Model modl) {
		verts.clear();
		model = modl;
		for (sf::Vector3f& vert : model.verts) {
			verts.push_back(vert);
		};
	}

};

