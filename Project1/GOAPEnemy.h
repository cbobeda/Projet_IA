#pragma once
#include "Enemy.hpp"
#include "GOAPAgent.h"
class GOAPEnemy : public Enemy
{
public:
    GOAPAgent agent;
    std::vector<sf::Vector2i> path;
    int i = 0;
    int pathIndex = 0;
    GOAPEnemy(float x, float y);
    void update(float deltaTime, Grid& grid,GOAPEnemy& enemy,sf::Vector2i player);
};
