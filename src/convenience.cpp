#include "convenience.hpp"
#include <cmath>

#define PI_DEF 3.14159265358979323846F

namespace cv
{

    float PI = PI_DEF;

    float norm(sf::Vector2f v) {
        return sqrt(v.x * v.x + v.y * v.y);
    }

    sf::Vector2f normalized(sf::Vector2f v) {
        float d = norm(v);
        if (d == 0.0f) return sf::Vector2f(0, 0);
        return v / d;
    }

    float distance(sf::Vector2f a, sf::Vector2f b) {
        return norm(a - b);
    }

}
