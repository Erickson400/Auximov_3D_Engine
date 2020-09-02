#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Camera.h"
#include <string>
#include <vector>
#define PI 3.14159265358979323846

namespace ax {
	//This is a fully Static Terrain (Not Dynamic)
	class Terrain : public sf::Drawable {
	public:
		Terrain(sf::Vector3i poffset);
		~Terrain();
		void load(const std::string perlinTex);
		void RenderUpdate(Camera& cam);

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const {
			state.texture = &m_tex; target.draw(m_vertArray, state);
		}

		void addQuad(sf::Vector2f position, float size);
		void addQuad(sf::Vector2f position, float size, sf::Color color);
		float Dist(sf::Vector3f a, sf::Vector3f b);

		const uint32_t WIDTH = 200, HEIGHT = 200; //Change depending on the size of the image
		const uint32_t VERT_SIZE = WIDTH * HEIGHT;
		sf::Vector3i offset;

		struct Point {
			sf::Vector3f pos = sf::Vector3f(0, 0, 0);
			sf::Color color = sf::Color::Black;
			float size = 0;
		};
		sf::Texture m_tex;
		sf::VertexArray m_vertArray;
		sf::Vector3i* m_Verteces = new sf::Vector3i[VERT_SIZE];
		sf::Vector3f* localRenderVerts = new sf::Vector3f[VERT_SIZE]; 
		Point* SortedPoints = new Point[VERT_SIZE]; uint32_t Sort_Stack = 0;

	};
}