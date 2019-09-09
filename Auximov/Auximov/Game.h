#pragma once
#include <iostream>
#ifndef  GRAPHICS_HPP
#include <SFML\Graphics.hpp>
#endif
#include "Objects.cpp"
#include <vector>

class Game {
public:
	float delta=0.0f;
	int FPS=0;
	char Hkey=0, Vkey=0;
	bool Up=false, Down=false, Right=false, Left=false, Shift=false, Space=false;
	bool LookUp = false, LookDown = false, LookLeft = false, LookRight = false;
	float MouseX=0, MouseY=0; float LastMouseX=0, LastMouseY=0;

	Game(sf::RenderWindow* app); ~Game();
	sf::RenderWindow* App = nullptr;
	sf::Event event = sf::Event();
	sf::View view1 = sf::View();

	sf::Texture *texture = new sf::Texture();
	Camera* camera = new Camera(sf::Vector3f(0,0,-4), *App);
	std::vector<Point> points;

	Model MyModel = Model("Media/mount.obj");
	Actor* MyActor;

	void FreeCameraControls();

	void Update();
	void EventHandling();
	void KeyCheck();
	void Rendering();
};
