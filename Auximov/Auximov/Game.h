#pragma once
#include <iostream>
#ifndef  GRAPHICS_HPP
#include <SFML\Graphics.hpp>
#endif
#include "Objects.cpp"
#include <vector>
#include <algorithm>

class Game {
public:
	Game(sf::RenderWindow* app); ~Game();
	sf::RenderWindow* App = nullptr;
	sf::Event event = sf::Event();
	sf::View view1 = sf::View();

	float delta=0.0f; int FPS=0;
	char Hkey=0, Vkey=0;
	float MouseX = 0, MouseY = 0;
	bool Up=false, Down=false, Right=false, Left=false, Shift=false, Space=false,
	LookUp=false, LookDown=false, LookLeft=false, LookRight=false;
	sf::Vector2i ScreenCenter = sf::Vector2i(App->getSize().x/2, App->getSize().y/2);
	
	sf::Texture texture, texture2 = sf::Texture();

	Camera camera = Camera(sf::Vector3f(0,0,-4), *App);
	std::vector<BufferVector> RenderBuffer;

	Model MyModel = Model("Media/mount.obj");
	Model Man = Model("Media/Fist.obj");
	//Model MyModel2 = Model("Media/mount.obj");
	Actor* MyActor;
	Actor* MyActor2;

	void FreeCameraControls();
	void RenderSortPoints(std::vector<BufferVector>& Buffer);

	void Update();
	void EventHandling();
	void AxisKeyCheck();
	void Rendering();
};
