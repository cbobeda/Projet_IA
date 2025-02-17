#pragma once
#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "Grid.hpp"
#include "Node.hpp"
#include <vector>

extern Grid grid;

class Pathfinding {
public:
    static std::vector<Node> findPath(Grid& grid, sf::Vector2i start, sf::Vector2i end);
};

#endif
