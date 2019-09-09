#include <iostream>
#ifndef GRAPHICS_HPP
#include <SFML\Graphics.hpp>
#endif
#include <math.h>

struct Camera {
public:
	Camera(sf::Vector3f Pos, sf::RenderWindow &win) : window(&win), Position(Pos) {};
	Camera(){};
	~Camera() {};
	
	sf::Vector3f Position = sf::Vector3f(0, 0, 0); 
	sf::Vector3f angle = sf::Vector3f(0, 0, 0);
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
			float scale = Dist(cam->FAR, RotatePosX.z) / Dist(0, RotatePosX.z);
			scale *= SpriteResize;
			temp.setScale(scale, scale);

			float ProjectedLengthX = temp.getGlobalBounds().width / 2;
			float ProjectedLengthY = temp.getGlobalBounds().height / 2;
			//Horizontal X Clipping
			float XPosClip = (RotatePosX.x / RotatePosX.z) * 1000;
			if (XPosClip+ProjectedLengthX >= -650 && XPosClip-ProjectedLengthX <= 650) {
				//Vertical Y Clipping
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



