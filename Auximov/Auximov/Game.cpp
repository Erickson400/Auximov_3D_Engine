#include "Game.h"
#define PI 3.14159265358979323846

Game::Game(sf::RenderWindow* app) : App(app) {
	view1.setCenter(sf::Vector2f(0,0));
	view1.setSize(sf::Vector2f((float)App->getSize().x, (float)App->getSize().y));

	texture.loadFromFile("Media/lol2.png");

	//Bottom
	for (int i = 0; i < 20; i++) {
		points.push_back(Point(sf::Vector3f(1, 1, (i*0.2)-1), *camera, texture));
		points.push_back(Point(sf::Vector3f(-1, 1, (i * 0.2) - 1), *camera, texture));
		points.push_back(Point(sf::Vector3f((i * 0.2) - 1, 1, 1), *camera, texture));
		points.push_back(Point(sf::Vector3f((i * 0.2) - 1, 1, -1), *camera, texture));
	}
	//Top
	for (int i = 0; i < 20; i++) {
		points.push_back(Point(sf::Vector3f(1, -1, (i * 0.2) - 1), *camera, texture));
		points.push_back(Point(sf::Vector3f((i * 0.2) - 1, -1, -1), *camera, texture));
		points.push_back(Point(sf::Vector3f((i * 0.2) - 1, -1, 1), *camera, texture));
		points.push_back(Point(sf::Vector3f(-1, -1, (i * 0.2) - 1), *camera, texture));
	}
	//Pillards
	for (int i = 0; i < 20; i++) {
		points.push_back(Point(sf::Vector3f(1, (i * 0.2) - 1, 1), *camera, texture));
		points.push_back(Point(sf::Vector3f(1, (i * 0.2) - 1, -1), *camera, texture));
		points.push_back(Point(sf::Vector3f(-1, (i * 0.2) - 1, 1), *camera, texture));
		points.push_back(Point(sf::Vector3f(-1, (i * 0.2) - 1, -1), *camera, texture));
	}
	
	points.push_back(Point(sf::Vector3f(0, 0, -2), *camera, texture));
}		

void Game::Update() {
	float RotateSpeed = 0.01;
	if (LookLeft)camera->angle.y += RotateSpeed;
	if(LookRight)camera->angle.y -= RotateSpeed;
	if (LookUp)camera->angle.x -= RotateSpeed;
	if (LookDown)camera->angle.x += RotateSpeed;

	camera->Position.z += (cos(camera->angle.y) * 0.03) * (float)Vkey;
	camera->Position.x -= (sin(camera->angle.y) * 0.03) * (float)Vkey;

	if (Right) {
		camera->Position.z += (cos(camera->angle.y-(PI/2)) * 0.03);
		camera->Position.x -= (sin(camera->angle.y-(PI/2)) * 0.03);
	}
	if (Left) {
		camera->Position.z += (cos(camera->angle.y + (PI / 2)) * 0.03);
		camera->Position.x -= (sin(camera->angle.y + (PI / 2)) * 0.03);
	}

	if (Shift) camera->Position.y += 0.009;
	if (Space) camera->Position.y -= 0.009;
}

void Game::Rendering() {
	App->clear();
	App->setView(view1);

	for (Point &point : points) {
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















Game::~Game() {
	App->close();
	points.clear();
	delete  camera, App;
}
