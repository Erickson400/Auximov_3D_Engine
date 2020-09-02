#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include "SFML/Graphics.hpp"
#define PI 3.14159265358979323846

namespace ax {
	class Camera {
	public:
		Camera(sf::Vector3f Pos, sf::RenderWindow& win);

		float Dist(float z1, float z2);
		void FreeCameraControls(float& delta, sf::Vector2f& AxisKeys, sf::Vector2f& LocalMouse, bool& Shift, bool& Space);

		const float NEAR = 0.1, FAR = 200; // Clipping Planes
		sf::Vector3f Position;
		sf::Vector3f angle = sf::Vector3f(0, 0, 0);
		sf::RenderWindow* window;
	};
}
#endif // !CAMERA_H


