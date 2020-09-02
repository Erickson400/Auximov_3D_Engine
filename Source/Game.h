#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "AXObjects/Objects.h"
#include "AXObjects/Mode7.h"
#include <vector>
#include <algorithm>
#define PI 3.14159265358979323846

class Game {
public:
	Game(sf::RenderWindow* app); ~Game();
	sf::Event event = sf::Event();
	float delta=0.0f; int FPS=0;

private:
	sf::RenderWindow* App = nullptr;
	sf::View view1 = sf::View();

	const sf::Vector2i SCREEN_CENTER = {App->getSize().x / 2, App->getSize().y / 2};
	sf::Vector2f AxisKeys = {0,0}; //X-Horizontal // Y-Vertical
	sf::Vector2f LocalMouse = {0,0};
	bool Up = false, Down = false, Right = false, Left = false, Shift = false, Space = false;
	
private:
	ax::Camera camera = { sf::Vector3f(1, -4, 1), *App };
	std::vector<ax::BufferVector> RenderBuffer;

	ax::Mode7 x{ "Media/zero1.png", camera, 70 };
	sf::Font font; sf::Text DebugLog;

public:
	void RenderSortPoints(std::vector<ax::BufferVector>& Buffer);
	void Update();
	void EventHandling();
	void AxisKeyCheck();
	void Rendering();
};
