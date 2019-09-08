#include <iostream>
#ifndef GRAPHICS_HPP
#include <SFML\Graphics.hpp>
#endif
#include <math.h>

struct Camera {
public:
	Camera(sf::Vector3f Pos, float angle, sf::RenderWindow &win) : window(&win), Position(Pos), angle(angle) {};
	Camera(){};
	~Camera() {};
	
	sf::Vector3f Position = sf::Vector3f(0, 0, 0); 
	float angle=0;
	const float NEAR = 1, FAR = 100;
	sf::RenderWindow *window = new sf::RenderWindow();
};

class Point {
public:
	Point(sf::Vector3f Pos, Camera& camera, sf::Texture& tex) : texture(tex), cam(&camera), Position(Pos) {};
	~Point() {};
	
	sf::Texture texture = sf::Texture();
	Camera* cam = new Camera();
	sf::Vector3f Position = sf::Vector3f(0,0,0);
	float SpriteResize = 0.007;

	void Render() {
		sf::Sprite temp; temp.setTexture(texture);
		temp.setOrigin(temp.getGlobalBounds().width / 2, temp.getGlobalBounds().height / 2);
		sf::Vector3f tempPos(Position);
		tempPos -= cam->Position;








		if (tempPos.z <= cam->FAR && tempPos.z >= cam->NEAR) {
			float scale = Dist(cam->FAR, tempPos.z) / Dist(0, tempPos.z);
			scale *= SpriteResize;
			temp.setScale(scale, scale);

			temp.setPosition((tempPos.x / tempPos.z) * 1000, (tempPos.y / tempPos.z) * 1000);
			cam->window->draw(temp);
		}
		
	}

private:
	float Dist(float z1, float z2) {
		//TopLength / BottomLength = SpriteScale
		return abs(z1 - z2);
	}

};



