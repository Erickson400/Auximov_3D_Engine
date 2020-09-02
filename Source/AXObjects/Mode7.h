#pragma once
#ifndef MODE7_H
#define MODE7_H

#include "SFML/Graphics.hpp"
#include "Camera.h"
#include <cmath>
//#define SCWIDTH 256
//#define SCHEIGHT 224
#define SCWIDTH 1300
#define SCHEIGHT 700
#define PI 3.14159265358979323846

namespace ax {
    class Mode7 {
    private:
        unsigned int m_T, m_L; // variable intermédiare m_T = m_screenHeght /2 et m_L = mscreenWidth / 2 (T: top, L: left)
        float m_FOV, m_D; // m_D distance du point de la caméra au plan de projection
        float m_cosinus = 0, m_sinus = 0;
        sf::Image m_image, m_imageTransformed;
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        ax::Camera* m_Cam; 

        sf::Uint8 pixels[SCWIDTH*SCHEIGHT*4];
        

    public:
        Mode7(std::string const& file, ax::Camera& p_Cam, float FOV);
        void Update();
        sf::Sprite getSprite();
    };
}
#endif // !MODE7_H


