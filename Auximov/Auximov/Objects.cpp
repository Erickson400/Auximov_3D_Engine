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
	~Camera() {};

	const float NEAR = 0.1, FAR = 100;
	sf::Vector3f Position = sf::Vector3f(0, 0, 0); 
	sf::Vector3f angle = sf::Vector3f(0, 0, 0);
	sf::RenderWindow *window = new sf::RenderWindow();
};

class Point {
public:
	Point(sf::Vector3f Pos, Camera& camera, sf::Texture& tex) : texture(tex), cam(&camera), Position(Pos) {};
	~Point() {};
	
	sf::Texture texture = sf::Texture();
	Camera* cam = new Camera();
	sf::Vector3f Position = sf::Vector3f(0,0,0);
	float SpriteResize = 0.001;

	void Render() {
		sf::Sprite temp; temp.setTexture(texture);
		temp.setOrigin(temp.getGlobalBounds().width / 2, temp.getGlobalBounds().height / 2);
		sf::Vector3f tempPos(Position);
		tempPos -= cam->Position;

		//Y Rotation
		sf::Vector3f RotatePosY(tempPos);
		RotatePosY.x = ((cos(cam->angle.y) * tempPos.x) + (sin(cam->angle.y) * tempPos.z));
		RotatePosY.z = ((-sin(cam->angle.y) * tempPos.x) + (cos(cam->angle.y) * tempPos.z));
		//X Rotation
		sf::Vector3f RotatePosX(RotatePosY);
		RotatePosX.y = ((cos(cam->angle.x) * RotatePosY.y) + (-sin(cam->angle.x) * RotatePosY.z));
		RotatePosX.z = ((sin(cam->angle.x) * RotatePosY.y) + (cos(cam->angle.x) * RotatePosY.z));

		//Z Clipping
		if (RotatePosX.z <= cam->FAR && RotatePosX.z >= cam->NEAR) {
			float scale = Dist(1000, RotatePosX.z) / Dist(0, RotatePosX.z);
			scale *= SpriteResize;
			temp.setScale(scale, scale);

			float ProjectedLengthX = temp.getGlobalBounds().width / 2;
			float ProjectedLengthY = temp.getGlobalBounds().height / 2;
			//X Clipping
			float XPosClip = (RotatePosX.x / RotatePosX.z) * 1000;
			if (XPosClip+ProjectedLengthX >= -650 && XPosClip-ProjectedLengthX <= 650) {
				//Y Clipping
				float YPosClip = (RotatePosX.y / RotatePosX.z) * 1000;
				if (YPosClip+ProjectedLengthY >= -350 && YPosClip-ProjectedLengthY <= 350) {
					temp.setPosition((RotatePosX.x / RotatePosX.z) * 1000, (RotatePosX.y / RotatePosX.z) * 1000);
					cam->window->draw(temp);
				}
			}
		}
	}

private:
	float Dist(float z1, float z2) {
		//TopLength / BottomLength = SpriteScale
		return abs(z1 - z2);
	}
};

class Model {
public:
	Model(std::string filename) {
		std::cout << "Model Created" << std::endl;
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
	Actor(sf::Vector3f pos, Model &modl, Camera* camera, sf::Texture& tex): texture(tex), cam(camera), Position(pos), model(modl) {
		points.clear();
		std::cout << "Actor Created" << std::endl;
		for (sf::Vector3f &vert : model.verts) {
			points.push_back(Point(sf::Vector3f(vert.x, -vert.y, vert.z), *cam, texture));
		};
	}
	Actor(){};
	~Actor() { delete cam; };

	std::vector<Point> points;
	sf::Texture texture = sf::Texture();
	Camera* cam = new Camera();
	sf::Vector3f Position;
	Model model;

	void Render() {
		for (Point& actorPoint : points) {
			actorPoint.Render();
		}
	}
	//void setModel(Model modl) {
	//	points.clear();
	//	model = modl;
	//	for (sf::Vector3f& vert : model.verts) {
	//		points.push_back(Point(vert, *cam, texture));
	//	};
	//}

};

