#include "Game.h"
#define PI 3.14159265358979323846

Game::Game(sf::RenderWindow* app) : App(app) {
	view1.setCenter(sf::Vector2f(0,0));
	view1.setSize(sf::Vector2f((float)App->getSize().x, (float)App->getSize().y));
	
	sf::Mouse::setPosition(sf::Vector2i(App->getSize().x/2, App->getSize().y/2), *App);

	texture->loadFromFile("Media/moon.png");
	MyActor = new Actor(sf::Vector3f(0, 0, 0), MyModel, camera, *texture);


	for (Point& point : MyActor->points) {
		point.Position.x *= 1;
		point.Position.y *= 1;
		point.Position.z *= 1;
	}
	//points.push_back(Point(sf::Vector3f(0,0,0), *camera, *texture));
}		

void Game::Update() {
	FreeCameraControls();

}

void Game::Rendering() {
	App->clear();
	App->setView(view1);

	MyActor->Render();

	for (Point& point : points) {
		point.Render();
	}

	App->display();
}

void Game::EventHandling() {
	switch (event.type) {
	case sf::Event::Closed: App->close(); break;
	case sf::Event::KeyPressed:
		switch (event.key.code) {
		case sf::Keyboard::Escape: App->close(); break;
		case sf::Keyboard::W: Up = true; break;
		case sf::Keyboard::A: Left = true; break;
		case sf::Keyboard::S: Down = true; break;
		case sf::Keyboard::D: Right = true; break;
		case sf::Keyboard::LShift: Shift = true; break;
		case sf::Keyboard::Space: Space = true; break;
		case sf::Keyboard::Up: LookUp = true; break;
		case sf::Keyboard::Left: LookLeft = true; break;
		case sf::Keyboard::Down: LookDown = true; break;
		case sf::Keyboard::Right: LookRight = true; break;
		}break;
	case sf::Event::KeyReleased:
		switch (event.key.code) {
		case sf::Keyboard::W: Up = false; break;
		case sf::Keyboard::A: Left = false; break;
		case sf::Keyboard::S: Down = false; break;
		case sf::Keyboard::D: Right = false; break;
		case sf::Keyboard::LShift: Shift = false; break;
		case sf::Keyboard::Space: Space = false; break;
		case sf::Keyboard::Up: LookUp = false; break;
		case sf::Keyboard::Left: LookLeft = false; break;
		case sf::Keyboard::Down: LookDown = false; break;
		case sf::Keyboard::Right: LookRight = false; break;
		}break;
	case sf::Event::MouseMoved:
		MouseX = sf::Mouse::getPosition(*App).x - (float)App->getSize().x / 2;
		MouseY = sf::Mouse::getPosition(*App).y - (float)App->getSize().y / 2;
		sf::Mouse::setPosition(sf::Vector2i(App->getSize().x / 2, App->getSize().y / 2), *App);
		break;
	}
}

void Game::KeyCheck() {
	if (Up && Down) {
		Vkey = 0;
	}
	else if (!Up && !Down) {
		Vkey = 0;
	}
	else if (!Up && Down) {
		Vkey = -1;
	}
	else if (Up && !Down) {
		Vkey = 1;
	}

	if (Right && Left) {
		Hkey = 0;
	}
	else if (!Right && !Left) {
		Hkey = 0;
	}
	else if (!Right && Left) {
		Hkey = -1;
	}
	else if (Right && !Left) {
		Hkey = 1;
	}
}


void Game::FreeCameraControls() {
	float RotateSpeed = 0.03 * delta;
	float moveSpeed = 4 * delta;

	camera->Position.z += (cos(camera->angle.y) * moveSpeed) * (float)Vkey;
	camera->Position.x -= (sin(camera->angle.y) * moveSpeed) * (float)Vkey;

	if (Right) {
		camera->Position.z += (cos(camera->angle.y - (PI / 2)) * moveSpeed);
		camera->Position.x -= (sin(camera->angle.y - (PI / 2)) * moveSpeed);
	}
	if (Left) {
		camera->Position.z += (cos(camera->angle.y + (PI / 2)) * moveSpeed);
		camera->Position.x -= (sin(camera->angle.y + (PI / 2)) * moveSpeed);
	}

	if (Shift) camera->Position.y += moveSpeed;
	if (Space) camera->Position.y -= moveSpeed;

	camera->angle.y -= RotateSpeed * MouseX;
	camera->angle.x += RotateSpeed * MouseY;
	MouseY = 0; MouseX = 0;

	if (LookUp)camera->angle.x -= RotateSpeed;
	if (LookDown)camera->angle.x += RotateSpeed;

}









Game::~Game() {
	App->close();
	points.clear();
	delete  MyActor, camera, App;
}
