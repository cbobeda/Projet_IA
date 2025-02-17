#include "GOAPEnemy.h"

GOAPEnemy::GOAPEnemy(float x, float y) : Enemy(x,y)
{
}


void GOAPEnemy::update(float deltaTime, Grid& grid,GOAPEnemy& enemy)
{
    agent.PerformActions(enemy);
    //agent.PrintState();
}
