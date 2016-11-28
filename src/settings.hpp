#ifndef SETTINGS_HH
#define SETTINGS_HH

#include <SFML/Graphics.hpp>
#include <string>

namespace s {

    extern std::string characterTextureFile;
    extern int characterRotationOffset;
    extern float blockDim;         // The dimension (length=width) of each block (tile)
    extern int viewHeight;

}

#endif
