class Terrain: public sf::Drawable{
    public:
        Terrain() { tex.loadFromFile("Media/grass.png"); };
        ~Terrain() {delete[] m_Verteces;}

        void load(const std::string perlinTex) {
            m_Verteces = new sf::Vector3f[WIDTH * HEIGHT];
            sf::Image map; map.loadFromFile(perlinTex);

            m_vertArray.setPrimitiveType(sf::Quads);
            m_vertArray.resize(WIDTH * HEIGHT * 4);

            //Read perlin pixels and set them to m_verteces
            for (uint32_t x = 0; x < WIDTH; x++) {
                for (uint32_t z = 0; z < HEIGHT; z++) {
                    float AverageColor = (float)(map.getPixel(x, z).r + map.getPixel(x, z).g + map.getPixel(x, z).b) / 3;
                    float pixelHeight = AverageColor / 255;
                    m_Verteces[x + z * WIDTH] = sf::Vector3f(x, pixelHeight * 20, z);
                }
            }
        }
        void updateDraw() {
            for (uint32_t x = 0; x < WIDTH; x++) {
                for (uint32_t z = 0; z < HEIGHT; z++) {
                    sf::Vertex* drawVerts = &m_vertArray[(x + z * WIDTH) * 4];
                    float castX = static_cast<float>(x)-50, castZ = static_cast<float>(z)-40;
                    float size = 20, offset = 40;
                    drawVerts[0].position = sf::Vector2f(castX * offset - size, castZ * offset - size);
                    drawVerts[1].position = sf::Vector2f(castX * offset + size, castZ * offset - size);
                    drawVerts[2].position = sf::Vector2f(castX * offset + size, castZ * offset + size);
                    drawVerts[3].position = sf::Vector2f(castX * offset - size, castZ * offset + size);

                    drawVerts[0].color = sf::Color(155*(m_Verteces[x + z * WIDTH].y), 255*(m_Verteces[x + z * WIDTH].y), 200+55*(m_Verteces[x + z * WIDTH].y));
                    drawVerts[1].color = sf::Color(155*(m_Verteces[x + z * WIDTH].y), 255*(m_Verteces[x + z * WIDTH].y), 200+55*(m_Verteces[x + z * WIDTH].y));
                    drawVerts[2].color = sf::Color(155*(m_Verteces[x + z * WIDTH].y), 255*(m_Verteces[x + z * WIDTH].y), 200+55*(m_Verteces[x + z * WIDTH].y));
                    drawVerts[3].color = sf::Color(155*(m_Verteces[x + z * WIDTH].y), 255*(m_Verteces[x + z * WIDTH].y), 200+55*(m_Verteces[x + z * WIDTH].y));

                    drawVerts[0].texCoords = sf::Vector2f(0, 0);
                    drawVerts[1].texCoords = sf::Vector2f(400.f, 0);
                    drawVerts[2].texCoords = sf::Vector2f(400.f, 400.f);
                    drawVerts[3].texCoords = sf::Vector2f(0, 400.f);
                } //665
            }
        }
        
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const {
            state.texture = &tex; target.draw(m_vertArray, state);
        }

        void addVertex(sf::Vector2f position, float size) {
            for (uint32_t x = 0; x < WIDTH; x++) {
                for (uint32_t z = 0; z < HEIGHT; z++) {
                    sf::Vertex* drawVerts = &m_vertArray[(x + z * WIDTH) * 4];
                    float castX = static_cast<float>(x) - 50, castZ = static_cast<float>(z) - 40;
                    float size = 20, offset = 40;
                    drawVerts[0].position = sf::Vector2f(castX * offset - size, castZ * offset - size);
                    drawVerts[1].position = sf::Vector2f(castX * offset + size, castZ * offset - size);
                    drawVerts[2].position = sf::Vector2f(castX * offset + size, castZ * offset + size);
                    drawVerts[3].position = sf::Vector2f(castX * offset - size, castZ * offset + size);

                    drawVerts[0].color = sf::Color(155 * (m_Verteces[x + z * WIDTH].y), 255 * (m_Verteces[x + z * WIDTH].y), 200 + 55 * (m_Verteces[x + z * WIDTH].y));
                    drawVerts[1].color = sf::Color(155 * (m_Verteces[x + z * WIDTH].y), 255 * (m_Verteces[x + z * WIDTH].y), 200 + 55 * (m_Verteces[x + z * WIDTH].y));
                    drawVerts[2].color = sf::Color(155 * (m_Verteces[x + z * WIDTH].y), 255 * (m_Verteces[x + z * WIDTH].y), 200 + 55 * (m_Verteces[x + z * WIDTH].y));
                    drawVerts[3].color = sf::Color(155 * (m_Verteces[x + z * WIDTH].y), 255 * (m_Verteces[x + z * WIDTH].y), 200 + 55 * (m_Verteces[x + z * WIDTH].y));

                    drawVerts[0].texCoords = sf::Vector2f(0, 0);
                    drawVerts[1].texCoords = sf::Vector2f(400.f, 0);
                    drawVerts[2].texCoords = sf::Vector2f(400.f, 400.f);
                    drawVerts[3].texCoords = sf::Vector2f(0, 400.f);
                } //665
            }
        }

        sf::Texture tex;
        sf::VertexArray m_vertArray;
        sf::Vector3f *m_Verteces;
        const uint16_t WIDTH = 100, HEIGHT = 100; //Change depending on the size of the image
    };