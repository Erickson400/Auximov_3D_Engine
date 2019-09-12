#include "Game.h"
#define PI 3.14159265358979323846

Game::Game(sf::RenderWindow* app) : App(app) {
	view1.setCenter(sf::Vector2f(0,0));
	view1.setSize(sf::Vector2f((float)App->getSize().x, (float)App->getSize().y));
	sf::Mouse::setPosition(sf::Vector2i(ScreenCenter), *App);

	texture.loadFromFile("Media/moon.png");
	texture2.loadFromFile("Media/dot.png");
	MyActor = new Actor(sf::Vector3f(0, 0, 0), MyModel, texture);

	//Push Actor Points to Buffer
	for (sf::Vector3f& vert : MyActor->verts) { //MyActor
		RenderBuffer.push_back(BufferVector(vert, MyActor->texture, MyActor->SpriteResize));
	}
	RenderBuffer[4].texture = &texture2;

}		

void Game::Update() {
	FreeCameraControls();
	std::cout << FPS << std::endl;


}

void Game::Rendering() {
	App->clear();
	App->setView(view1);

	//Sort & Render Points
	RenderSortPoints(RenderBuffer);

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
		MouseX = sf::Mouse::getPosition(*App).x - (float)ScreenCenter.x;
		MouseY = sf::Mouse::getPosition(*App).y - (float)ScreenCenter.y;
		sf::Mouse::setPosition(sf::Vector2i(ScreenCenter), *App);
		break;
	}
}

void Game::AxisKeyCheck() {
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

	//Movement
	camera.Position.z += (cos(camera.angle.y) * moveSpeed) * (float)Vkey;
	camera.Position.x -= (sin(camera.angle.y) * moveSpeed) * (float)Vkey;
	if (Right) {
		camera.Position.z += (cos(camera.angle.y - (PI / 2)) * moveSpeed);
		camera.Position.x -= (sin(camera.angle.y - (PI / 2)) * moveSpeed);
	}
	if (Left) {
		camera.Position.z += (cos(camera.angle.y + (PI / 2)) * moveSpeed);
		camera.Position.x -= (sin(camera.angle.y + (PI / 2)) * moveSpeed);
	}
	if (Shift) camera.Position.y += moveSpeed;
	if (Space) camera.Position.y -= moveSpeed;

	//Camera Angle
	camera.angle.y -= RotateSpeed * MouseX;
	camera.angle.x += RotateSpeed * MouseY;

	if (LookUp)camera.angle.x -= RotateSpeed * 40;
	if (LookDown)camera.angle.x += RotateSpeed * 40;
	if (LookLeft)camera.angle.y += RotateSpeed * 40;
	if (LookRight)camera.angle.y -= RotateSpeed * 40;
	MouseY = 0; MouseX = 0;
}

void Game::RenderSortPoints(std::vector<BufferVector>& Buffer) {
	std::vector<BufferVector> SortedBuffer;

	//Get Perspective Positions
	for (BufferVector& vert : Buffer) {
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
		SortedBuffer.push_back(BufferVector(RotatePosX, *vert.texture, vert.SpriteResize));
	}

	//Sort vector
	std::sort(SortedBuffer.begin(), SortedBuffer.end(), [](BufferVector& a, BufferVector& b) {
		return a.Position.z > b.Position.z;
	});

	//Render
	for (BufferVector& vert : SortedBuffer) {
		sf::Sprite temp; temp.setTexture(*vert.texture);
		temp.setOrigin(temp.getGlobalBounds().width / 2, temp.getGlobalBounds().height / 2);

		//Z Clipping
		if (vert.Position.z <= camera.FAR && vert.Position.z >= camera.NEAR) {
			float scale = camera.Dist(1000, vert.Position.z) / camera.Dist(0, vert.Position.z);
			scale *= vert.SpriteResize;
			temp.setScale(scale, scale);

			float ProjectedLengthX = temp.getGlobalBounds().width / 2;
			float ProjectedLengthY = temp.getGlobalBounds().height / 2;
			//X Clipping
			float XPosClip = (vert.Position.x / vert.Position.z) * 1000;
			if (XPosClip + ProjectedLengthX >= -650 && XPosClip - ProjectedLengthX <= 650) {
				//Y Clipping
				float YPosClip = (vert.Position.y / vert.Position.z) * 1000;
				if (YPosClip + ProjectedLengthY >= -350 && YPosClip - ProjectedLengthY <= 350) {

					temp.setPosition((vert.Position.x / vert.Position.z) * 1000, (vert.Position.y / vert.Position.z) * 1000);
					camera.window->draw(temp);
				}
			}
		}
	}

}


















Game::~Game() {
	App->close();
	RenderBuffer.clear();
	delete  MyActor, camera, App;
}
