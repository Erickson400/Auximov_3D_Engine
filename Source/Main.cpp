#include <iostream>
#include <SFML\Graphics.hpp>
#include "Game.h"

int main() {
	sf::RenderWindow* App = new sf::RenderWindow(sf::VideoMode(1300, 700), "Auximov_3D_Engine", sf::Style::Titlebar | sf::Style::Close);
	App->setFramerateLimit(60);
	App->setKeyRepeatEnabled(true);
	App->setMouseCursorVisible(false);
	Game* game = new Game(App);

	while (App->isOpen()) {
		sf::Clock timer;
		sf::Time elapsed1 = timer.getElapsedTime();
		while (App->pollEvent(game->event)) { game->EventHandling(); }
		game->Update();
		game->AxisKeyCheck();
		game->Rendering();
		sf::Time elapsed2 = elapsed1 - timer.getElapsedTime();
		game->delta = -elapsed2.asSeconds();
		game->FPS = 1.0/timer.getElapsedTime().asSeconds();
	}
	delete game, App;
	return 0;
}
