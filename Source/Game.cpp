#include "Game.h"

Game::Game(sf::RenderWindow* app) : App(app) {
	view1.setCenter(sf::Vector2f(0, 0));
	view1.setSize(sf::Vector2f(App->getSize().x, App->getSize().y));
	//view1.setSize(sf::Vector2f(App->getSize().x/4, App->getSize().y/4));
	sf::Mouse::setPosition(sf::Vector2i(SCREEN_CENTER), *App);

	font.loadFromFile("Media/font.otf");
	DebugLog.setFont(font); DebugLog.setFillColor(sf::Color::White);
	DebugLog.setPosition(-650, -350);


}

void Game::Update() {
	camera.FreeCameraControls(delta, AxisKeys, LocalMouse, Shift, Space);
	//DebugLog.setString("X: " + std::to_string(camera.Position.x) + ", Y: " + std::to_string(camera.Position.y) + ", Z: " + std::to_string(camera.Position.z)+ ", Angle: " + std::to_string(camera.angle.y*(180/PI)));
	DebugLog.setString("FPS: " + std::to_string(FPS));

	x.Update();
}

void Game::Rendering() {
	App->clear(sf::Color(100, 100, 100));
	App->setView(view1);

	App->draw(x.getSprite());

	App->draw(DebugLog);

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
		}break;
	case sf::Event::KeyReleased:
		switch (event.key.code) {
		case sf::Keyboard::W: Up = false; break;
		case sf::Keyboard::A: Left = false; break;
		case sf::Keyboard::S: Down = false; break;
		case sf::Keyboard::D: Right = false; break;
		case sf::Keyboard::LShift: Shift = false; break;
		case sf::Keyboard::Space: Space = false; break;
		}break;
	case sf::Event::MouseMoved:
		LocalMouse.x = sf::Mouse::getPosition(*App).x - static_cast<float>(SCREEN_CENTER.x);
		LocalMouse.y = sf::Mouse::getPosition(*App).y - static_cast<float>(SCREEN_CENTER.y);
		sf::Mouse::setPosition(sf::Vector2i(SCREEN_CENTER), *App);
		break;
	}
}

void Game::AxisKeyCheck() {
	//Vertical
	if (Up) {
		if (Down) {
			AxisKeys.y = 0;
		}
		else {
			AxisKeys.y = 1;
		}
	}
	else {
		if (Down) {
			AxisKeys.y = -1;
		}
		else {
			AxisKeys.y = 0;
		}
	}

	//Horizontal
	if (Right) {
		if (Left) {
			AxisKeys.x = 0;
		}
		else {
			AxisKeys.x = 1;
		}
	}
	else {
		if (Left) {
			AxisKeys.x = -1;
		}
		else {
			AxisKeys.x = 0;
		}
	}
}

void Game::RenderSortPoints(std::vector<ax::BufferVector>& Buffer) {
	std::vector<ax::BufferVector> SortedBuffer;

	//Get Perspective Positions
	for (ax::BufferVector& vert : Buffer) {
		sf::Vector3f tempPos(vert.Position);
		tempPos -= camera.Position;

		//Y Rotation
		sf::Vector3f RotatePosY(tempPos);
		RotatePosY.x = ((cos(camera.angle.y) * tempPos.x) + (sin(camera.angle.y) * tempPos.z));
		RotatePosY.z = ((-sin(camera.angle.y) * tempPos.x) + (cos(camera.angle.y) * tempPos.z));
		//X Rotation
		sf::Vector3f RotatePosX(RotatePosY);
		RotatePosX.y = ((cos(camera.angle.x) * RotatePosY.y) + (-sin(camera.angle.x) * RotatePosY.z));
		RotatePosX.z = ((sin(camera.angle.x) * RotatePosY.y) + (cos(camera.angle.x) * RotatePosY.z));

		//Clip Vectors that are off distance/screen
		sf::Sprite temp;
		temp.setTexture(*vert.texture);
		temp.setOrigin(temp.getGlobalBounds().width / 2, temp.getGlobalBounds().height / 2);

		//Z Clipping
		if (RotatePosX.z <= camera.FAR && RotatePosX.z >= camera.NEAR) {
			float scale = camera.Dist(1000, RotatePosX.z) / camera.Dist(0, RotatePosX.z);
			scale *= vert.SpriteResize;
			temp.setScale(scale, scale);

			float ProjectedLengthX = temp.getGlobalBounds().width / 2;
			float ProjectedLengthY = temp.getGlobalBounds().height / 2;
			//X Clipping
			float XPosClip = (RotatePosX.x / RotatePosX.z) * 1000;
			if (XPosClip + ProjectedLengthX >= -650 && XPosClip - ProjectedLengthX <= 650) {
				//Y Clipping
				float YPosClip = (RotatePosX.y / RotatePosX.z) * 1000;
				if (YPosClip + ProjectedLengthY >= -350 && YPosClip - ProjectedLengthY <= 350) {
					SortedBuffer.push_back(ax::BufferVector(RotatePosX, *vert.texture, vert.SpriteResize, vert.ID));
				}
			}
		}
	}

	//Sort vector
	std::sort(SortedBuffer.begin(), SortedBuffer.end(), [](ax::BufferVector& a, ax::BufferVector& b) {
		return a.Position.z > b.Position.z;
		});

	//Render
	for (ax::BufferVector& vert : SortedBuffer) {
		sf::Sprite temp;
		temp.setTexture(*vert.texture);
		temp.setOrigin(temp.getGlobalBounds().width / 2, temp.getGlobalBounds().height / 2);

		float scale = camera.Dist(1000, vert.Position.z) / camera.Dist(0, vert.Position.z);
		scale *= vert.SpriteResize;
		temp.setScale(scale, scale);
		temp.setPosition((vert.Position.x / vert.Position.z) * 1000, (vert.Position.y / vert.Position.z) * 1000);
		camera.window->draw(temp);
	}
}


















Game::~Game() {
	//delete terrain;
	RenderBuffer.clear();
	App->close();
	delete App;
}








