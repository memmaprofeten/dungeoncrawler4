#include <cmath>
#include <SFML/Graphics.hpp>

/**
 * A namespace containing convenience functions for the game.
 * The functionality includes some basic linear algebra functions and other
 * convenient functionality.
 */
namespace cv
{

    /**
     * Calculates the norm, or length, of a vector.
     */
    float norm(sf::Vector2f v) {
        return sqrt(v.x * v.x + v.y * v.y);
    }

    /**
     * Returns a new vector that is the parameter vector normalized.
     */
    sf::Vector2f normalized(sf::Vector2f v) {
        return v / norm(v);
    }

}
