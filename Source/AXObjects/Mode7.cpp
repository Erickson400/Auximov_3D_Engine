#include "Mode7.h"

namespace ax {
    Mode7::Mode7(std::string const& file, ax::Camera& p_Cam, float FOV) : m_Cam(&p_Cam) {
        m_sprite.setPosition(sf::Vector2f(-SCWIDTH / 2, -SCHEIGHT / 2));

        //Set Screen variables
        //m_imageTransformed.create(SCWIDTH, SCHEIGHT, sf::Color::Black);
        for (int y = 0; y < SCHEIGHT; y++) {
            for (int x = 0; x < SCWIDTH; x++) {
                pixels[(x + y * SCWIDTH)*4]     = 0;
                pixels[(x + y * SCWIDTH)*4 + 1] = 0;
                pixels[(x + y * SCWIDTH)*4 + 2] = 0;
                pixels[(x + y * SCWIDTH)*4 + 3] = 0;
            }
        }


        m_texture.create(SCWIDTH, SCHEIGHT);
        m_T = SCHEIGHT / 2; 
        m_L = SCWIDTH / 2;
        
        //load texture
        if (!m_image.loadFromFile(file)) m_image.loadFromFile("Media/Error.png");

        //Set FOV
        m_FOV = FOV;
        m_D = m_T / std::tan(m_FOV * (PI/360));
    }

    void Mode7::Update() {
        //From camera to Mode7 Position
        float speed = 6;
        sf::Vector3f LocalCamPos = { -m_Cam->Position.x * speed, m_Cam->Position.y * speed, m_Cam->Position.z * speed };

        //Update Cos/Sin of the angle
        m_cosinus = std::cos(-m_Cam->angle.y);
        m_sinus = std::sin(-m_Cam->angle.y);

        const sf::Uint8* ImagePxPtr = m_image.getPixelsPtr();
        for (unsigned int ys = m_T+40; ys < SCHEIGHT; ys++) {
            for (unsigned int xs = 0; xs < SCWIDTH; xs++) {
                float const xw = LocalCamPos.x - LocalCamPos.y * ((float)xs - (float)m_L) / ((float)m_T - (float)ys) * m_cosinus - m_D * LocalCamPos.y / ((float)m_T - (float)ys) * m_sinus;
                float const zw = LocalCamPos.z - LocalCamPos.y * ((float)xs - (float)m_L) / ((float)m_T - (float)ys) * m_sinus + m_D * LocalCamPos.y / ((float)m_T - (float)ys) * m_cosinus;

                if (xw < 0 || zw < 0 || xw >= m_image.getSize().x || zw >= m_image.getSize().y) {
                    pixels[(xs + ys * SCWIDTH) * 4 + 3] = 0;
                    //m_imageTransformed.setPixel(xs, ys, sf::Color::Transparent); //sf::Color::Black
                }
                else {
                    //Set Pixel
                    int size = m_image.getSize().x;
                    sf::Uint8* pixel = &pixels[(xs + ys * SCWIDTH) * 4];
                    const sf::Uint8* pixel2 = &ImagePxPtr[(static_cast<unsigned int>(xw) + static_cast<unsigned int>(zw)* size) * 4];

                    //Loop up the Image SetPixel .cpp on github to understand
                    *pixel++ = *pixel2++; //R
                    *pixel++ = *pixel2++; //G
                    *pixel++ = *pixel2++; //B
                    *pixel++ = *pixel2++; //A
                    //m_imageTransformed.setPixel(xs, ys, m_image.getPixel((unsigned int)xw, (unsigned int)zw));
                }
            }
        }

        /*        for (unsigned int ys = m_T+1; ys < SCHEIGHT; ys+=2) {
            for (unsigned int xs=0; xs < SCWIDTH; xs++) {
                float const xw = LocalCamPos.x - LocalCamPos.y * ((float)xs - (float)m_L) / ((float)m_T - (float)ys) * m_cosinus - m_D * LocalCamPos.y / ((float)m_T - (float)ys) * m_sinus;
                float const zw = LocalCamPos.z - LocalCamPos.y * ((float)xs - (float)m_L) / ((float)m_T - (float)ys) * m_sinus + m_D * LocalCamPos.y / ((float)m_T - (float)ys) * m_cosinus;

                if (xw < 0 || zw < 0 || xw >= m_image.getSize().x || zw >= m_image.getSize().y) {
                    pixels[(xs+ys*SCWIDTH)*4 + 3] = 0;
                    //m_imageTransformed.setPixel(xs, ys, sf::Color::Transparent); //sf::Color::Black
                } else {
                    //Set Pixel
                    int size = m_image.getSize().x;
                    sf::Uint8* pixel = &pixels[(xs + ys * SCWIDTH) * 4];
                    const sf::Uint8* pixel2 = &ImagePxPtr[(static_cast<unsigned int>(xw) + static_cast<unsigned int>(zw)* size) * 4];

                    //Loop up the Image SetPixel .cpp on github to understand
                    *pixel++ = *pixel2++; //R
                    *pixel++ = *pixel2++; //G
                    *pixel++ = *pixel2++; //B
                    *pixel++ = *pixel2++; //A
                    //m_imageTransformed.setPixel(xs, ys, m_image.getPixel((unsigned int)xw, (unsigned int)zw));
                }
            }
        }*/
    }

    sf::Sprite Mode7::getSprite() {
        m_texture.update(pixels);
        //m_texture.update(m_imageTransformed);
        m_sprite.setTexture(m_texture);
        return m_sprite;
    }
}


