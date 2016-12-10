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

    extern float PI;

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

    /**
     * Takes as input a grid of penetrable/non-penetrable booleans, start
     * coordinates and a vector of target coordinates, and returns a vector of
     * booleans where each boolean tells whether or not there exists a path
     * between the starting point and the target point at the corresponding
     * index.
     */
    std::vector<bool> pathExists(const std::vector<std::vector<bool>>& grid, sf::Vector2i start, std::vector<sf::Vector2i> targets);

}

#endif
