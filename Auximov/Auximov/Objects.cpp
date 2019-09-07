#include <iostream>
#ifndef GRAPHICS_HPP
#include <SFML\Graphics.hpp>
#endif

struct Camera {
public:
	Camera(sf::Vector3f Pos, float angle, sf::RenderWindow &win) : window(&win), Position(Pos), angle(angle) {};
	Camera(){};
	~Camera() {};
	
	sf::Vector3f Position = sf::Vector3f(0, 0, 0); 
	float angle=0;
	const sf::Vector2f PLANECLIPS = sf::Vector2f(1, 100);
	sf::RenderWindow *window = new sf::RenderWindow();
};

class Point {
public:
	Point(sf::Vector3f Pos, Camera& camera, sf::Texture& tex) : texture(tex), cam(camera), Position(Pos) {};
	~Point() {};
	
	sf::Texture texture = sf::Texture();
	Camera cam = Camera();
	sf::Vector3f Position = sf::Vector3f(0,0,0);

	void Render() {
		sf::Sprite temp; temp.setTexture(texture);
		temp.setOrigin(temp.getScale().x/2, temp.getScale().y / 2);

		sf::Vector3f tempPos(Position);
		tempPos = tempPos - cam.Position;

		temp.setPosition((tempPos.x/ tempPos.z)*1000, (tempPos.y/ tempPos.z)*1000);
		cam.window->draw(temp);
	}

	

};



