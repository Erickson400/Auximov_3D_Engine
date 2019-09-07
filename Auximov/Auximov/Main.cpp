#include <iostream>
#ifndef  GRAPHICS_HPP
#include <SFML\Graphics.hpp>
#endif
#include "Game.h"

int main(int argc, char** argv) {
	sf::RenderWindow* App = new sf::RenderWindow(sf::VideoMode(1300, 700), "Auximov_3D_Engine", sf::Style::Titlebar | sf::Style::Close);
	App->setFramerateLimit(60);
	App->setKeyRepeatEnabled(false);
	Game* game = new Game(App);

	while (App->isOpen()) {
		sf::Clock timer;
		sf::Time elapsed1 = timer.getElapsedTime();
		while (App->pollEvent(game->event)) { game->EventHandling(); }
		game->Update();
		game->KeyCheck();
		game->Rendering();
		sf::Time elapsed2 = elapsed1 - timer.getElapsedTime();
		game->delta = (float)-elapsed2.asMilliseconds();
	}
	delete game, App;
	return 0;
}
