#pragma once
#include <iostream>
#ifndef  GRAPHICS_HPP
#include <SFML\Graphics.hpp>
#endif

class Game {
public:
	float delta=0.0f;
	char Hkey=0, Vkey=0;
	bool Up=false, Down=false, Right=false, Left=false;

	Game(sf::RenderWindow* app); ~Game();
	sf::RenderWindow* App = nullptr;
	sf::Event event = sf::Event();
	sf::View view1 = sf::View();

	void Update();
	void EventHandling();
	void KeyCheck();
	void Rendering();
};
