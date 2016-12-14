#include "convenience.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>

#define PI_DEF 3.14159265358979323846F

namespace cv
{

    float PI = PI_DEF;

    bool isZero(sf::Vector2f v) {
        return v.x == 0.0f && v.y == 0.0f;
    }

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

    float approxDistance(sf::Vector2f a, sf::Vector2f b) {
        return abs(b.x - a.x) + abs(b.y - a.y);
    }

    float dotP(sf::Vector2f a, sf::Vector2f b) {
        return a.x * b.x + a.y * b.y;
    }

    std::vector<bool> pathExists(const std::vector<std::vector<bool>>& grid, sf::Vector2i start, std::vector<sf::Vector2i> targets) {
        int width = grid.size();
        int height = grid[0].size();
        if (start.x < 0 || start.y < 0 || start.x >= width || start.y >= height) throw std::runtime_error("Called pathExists with parameter coordinates out of bounds!");
        for (auto t : targets) if ((t.x < 0 || t.y < 0 || t.x >= width || t.y >= height)) throw std::runtime_error("Called pathExists with parameter coordinates out of bounds!");

        std::vector<bool> res(targets.size(), false);
        std::vector<std::vector<bool>> visited(width, std::vector<bool>(height, false));
        std::vector<sf::Vector2i> queue;
        std::vector<sf::Vector2i> newQueue;
        queue.push_back(start);
        while (true) {
            for (auto v : queue) {
                for (int i=0; i<(int)targets.size(); ++i) if (v.x == targets[i].x && v.y == targets[i].y) res[i] = true;
                for (int i=-1; i<2; ++i) for (int j=-1; j<2; ++j) {
                    int x = v.x + i;
                    int y = v.y + j;
                    if (i != j && i * j == 0 && x >= 0 && y >= 0 && x < width && y < height && !visited[x][y] && !grid[x][y]) {
                        visited[x][y] = true;
                        newQueue.push_back(sf::Vector2i(x, y));
                    }
                }
            }
            queue = newQueue;
            newQueue.clear();
            if (queue.size() == 0) break;   // The algorithm is finished when all reachable cells have been checked.
        }
        return res;
    }

}
