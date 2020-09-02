#include "Terrain.h"

namespace ax {
	Terrain::Terrain(sf::Vector3i poffset): offset(poffset) { m_tex.loadFromFile("Media/dot.png"); };
	Terrain::~Terrain() { delete[] m_Verteces, localRenderVerts, SortedPoints;};

	void Terrain::load(const std::string perlinTex) {
		//Set array's Primitive type
		m_vertArray.setPrimitiveType(sf::Quads);

		//Read perlin pixels and set them to m_verteces
		sf::Image map; map.loadFromFile(perlinTex);
		for (uint32_t x = 0; x < WIDTH; x++) {
			for (uint32_t z = 0; z < HEIGHT; z++) {
				float AverageColor = static_cast<float>(map.getPixel(x, z).r + map.getPixel(x, z).g + map.getPixel(x, z).b) / 3;
				float pixelHeight = AverageColor / 255; //gives number from 0 to 1
				m_Verteces[x + z * WIDTH] = sf::Vector3i(x+offset.x, pixelHeight * 20, z);
			}
		}
	}

	void Terrain::addQuad(sf::Vector2f position, float size) {
		//Create Quad verteces and Move them
		sf::Vertex localQuadVerts[] = {
			sf::Vertex(sf::Vector2f(-size,-size), sf::Vector2f(0              , 0)),
			sf::Vertex(sf::Vector2f(-size, size), sf::Vector2f(0              , m_tex.getSize().y)),
			sf::Vertex(sf::Vector2f(size , size), sf::Vector2f(m_tex.getSize().x, m_tex.getSize().y)),
			sf::Vertex(sf::Vector2f(size ,-size), sf::Vector2f(m_tex.getSize().x, 0))
		};
		for (uint32_t i = 0; i < 4; i++) {
			localQuadVerts[i].position += position;
		}
		//Add the Quad to the vertArray sizeof(localQuadVerts) / sizeof(localQuadVerts[0])
		for (uint32_t i = 0; i < 4; i++) {
			m_vertArray.append(localQuadVerts[i]);
		}
	}
	void Terrain::addQuad(sf::Vector2f position, float size, sf::Color color) {
		//Create and Move the Quad's verteces
		sf::Vertex localQuadVerts[] = {
			sf::Vertex(sf::Vector2f(-size,-size), color, sf::Vector2f(0              , 0)),
			sf::Vertex(sf::Vector2f(-size, size), color, sf::Vector2f(0              , m_tex.getSize().y)),
			sf::Vertex(sf::Vector2f(size , size), color, sf::Vector2f(m_tex.getSize().x, m_tex.getSize().y)),
			sf::Vertex(sf::Vector2f(size ,-size), color, sf::Vector2f(m_tex.getSize().x, 0))
		};
		for (uint32_t i = 0; i < sizeof(localQuadVerts) / sizeof(localQuadVerts[0]); i++) {
			localQuadVerts[i].position += position;
		}
		//Add the Quad to the vertArray
		for (uint32_t i = 0; i < sizeof(localQuadVerts) / sizeof(localQuadVerts[0]); i++) {
			m_vertArray.append(localQuadVerts[i]);
		}
	}
	inline float Terrain::Dist(sf::Vector3f a, sf::Vector3f b) {
		return pow(b.x-a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2);
	}

	void Terrain::RenderUpdate(Camera& camera) {
		m_vertArray.clear(); //Clear the draw array before updating

		//Reset the local verts to m_Verteces (Only add verts inside the distance)
		uint32_t localRender_Size = 0;
		for (uint32_t i = 0; i < VERT_SIZE; i++) {
			if (Dist(sf::Vector3f(m_Verteces[i].x, m_Verteces[i].y, m_Verteces[i].z), camera.Position) < 10000) {
				localRenderVerts[localRender_Size] = sf::Vector3f(m_Verteces[i].x, m_Verteces[i].y, m_Verteces[i].z);
				localRender_Size++;
			}
		}

		//Get Perspective Position (move and rotate), Then Clip
		for (uint32_t i = 0; i < localRender_Size; i++) {
			sf::Vector3f tempPos(localRenderVerts[i]);
			//Move relative to the camera
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
			float SpriteResize;
			//Z Clipping
			if (RotatePosX.z <= camera.FAR && RotatePosX.z >= camera.NEAR) {
				SpriteResize = camera.Dist(1000, RotatePosX.z) / camera.Dist(0, RotatePosX.z);
				float ProjectedX = (RotatePosX.x / RotatePosX.z) * 1000;
				float ProjectedY = (RotatePosX.y / RotatePosX.z) * 1000;

				//X Clipping
				if (ProjectedX + SpriteResize >= -650 && ProjectedX - SpriteResize <= 650) {
					//Y Clipping
					if (ProjectedY + SpriteResize >= -350 && ProjectedY - SpriteResize <= 350) {
						SortedPoints[Sort_Stack].pos = sf::Vector3f(ProjectedX, ProjectedY, RotatePosX.z);
						SortedPoints[Sort_Stack].size = SpriteResize;
						SortedPoints[Sort_Stack].color = sf::Color(localRenderVerts[i].y * 105, localRenderVerts[i].y * 100, 200);
						Sort_Stack++;
					}
				}
			}
		}
		
		//Sort array
		std::sort(SortedPoints, SortedPoints + Sort_Stack, [](Point a, Point b) {
			return a.pos.z > b.pos.z;
		});
		
		//Render
		for (uint32_t i = 0; i < Sort_Stack; i++) {
			addQuad(sf::Vector2f(SortedPoints[i].pos.x, SortedPoints[i].pos.y), SortedPoints[i].size*0.8, SortedPoints[i].color);
		}

		Sort_Stack = 0;
	}

}
