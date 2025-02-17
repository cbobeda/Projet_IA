#pragma once
#include "Enemy.hpp"
#include "GOAPAgent.h"
class GOAPEnemy : public Enemy
{
private:
    GOAPAgent agent;
public:
    int i = 0;
    GOAPEnemy(float x, float y);
    void update(float deltaTime, Grid& grid,GOAPEnemy& enemy);
};
