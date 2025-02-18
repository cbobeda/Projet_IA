#pragma once
#include "Enemy.hpp"
#include "GOAPAgent.h"
class GOAPEnemy : public Enemy
{
private:
    GOAPAgent agent;
public:
    std::vector<sf::Vector2i> path;
    int i = 0;
    int pathIndex = 0;
    GOAPEnemy(float x, float y);
    void update(float deltaTime, Grid& grid,GOAPEnemy& enemy);
};
