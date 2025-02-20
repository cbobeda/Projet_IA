#pragma once
#include "GOAPPlanner.h"
class GOAPAgent
{
private:
    GOAPPlanner planner;
public:
    State state;
    GOAPAgent();
    void PerformActions(GOAPEnemy& enemy,sf::Vector2i player);
    void PrintState();
};
