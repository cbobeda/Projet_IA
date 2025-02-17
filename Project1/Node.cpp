#include "Node.hpp"
#include <cmath>

Node::Node(sf::Vector2i pos) : position(pos), gCost(0), hCost(0), fCost(0), parent(nullptr) {}

void Node::calculateCosts(Node* end, int newG) {
    gCost = newG;
    hCost = std::abs(position.x - end->position.x) + std::abs(position.y - end->position.y);                   //manathan
    //hCost = std::sqrt(std::pow(position.x - end->position.x, 2) + std::pow(position.y - end->position.y, 2));   //euclidienne
    //hCost = std::fmax(std::abs(position.x - end->position.x), std::abs(position.y - end->position.y));       //chebyshev
    fCost = gCost + hCost;
}