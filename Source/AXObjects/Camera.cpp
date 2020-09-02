#include "Camera.h"

namespace ax {
	Camera::Camera(sf::Vector3f Pos, sf::RenderWindow& win) : window(&win), Position(Pos) {};

	float Camera::Dist(float z1, float z2) {
		//TopLength / BottomLength = SpriteScale
		return abs(z1 - z2);
	}
	void Camera::FreeCameraControls(float& delta, sf::Vector2f& AxisKeys, sf::Vector2f& LocalMouse, bool& Shift, bool& Space) {
		float RotateSpeed = 0.03 * delta;
		float moveSpeed = 40 * delta;

		//Movement
		Position.z += (cos(angle.y) * moveSpeed) * AxisKeys.y; //forward 
		Position.x -= (sin(angle.y) * moveSpeed) * AxisKeys.y;

		Position.z += (cos(angle.y - (PI / 2)) * moveSpeed) * AxisKeys.x; //Strafe
		Position.x -= (sin(angle.y - (PI / 2)) * moveSpeed) * AxisKeys.x;

		if (Shift) Position.y += moveSpeed; // Up/Down
		if (Space) Position.y -= moveSpeed;

		//Camera Angle
		angle.y -= RotateSpeed * LocalMouse.x;
		angle.x += RotateSpeed * LocalMouse.y;

		//Clamp the Pitch
		if (angle.x >= PI / 2)angle.x = PI / 2;
		if (angle.x <= -PI / 2)angle.x = -PI / 2;
		LocalMouse = sf::Vector2f(0, 0);
	}

}
