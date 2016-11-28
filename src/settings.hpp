#ifndef SETTINGS_HH
#define SETTINGS_HH

#include <SFML/Graphics.hpp>
#include <string>

namespace s {

    std::string characterTextureFile = "../resources/img/character_32.png";
    int characterRotationOffset = 270;
    float blockDim = 10.0f;         // The dimension (length=width) of each block (tile)
    int viewHeight = 150;

}

#endif
