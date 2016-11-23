#include "convenience.hpp"
#include <cmath>

namespace cv
{

    float norm(sf::Vector2f v) {
        return sqrt(v.x * v.x + v.y * v.y);
    }

    sf::Vector2f normalized(sf::Vector2f v) {
        float d = norm(v);
        if (d == 0.0f) return sf::Vector2f(0, 0);
        return v / d;
    }

}
