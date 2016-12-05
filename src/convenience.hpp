#ifndef CONVENIENCE_HH
#define CONVENIENCE_HH

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
    float norm(sf::Vector2f v);

    /**
     * Returns a new vector that is the parameter vector v normalized.
     * If the norm of v is zero, returns the zero vector.
     */
    sf::Vector2f normalized(sf::Vector2f v);

    /**
     * Returns the distance between two points in the plane.
     */
    float distance(sf::Vector2f a, sf::Vector2f b);

}

#endif
