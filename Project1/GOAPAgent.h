#pragma once
#include "GOAPPlanner.h"
class GOAPAgent
{
private:
    State state;
    GOAPPlanner planner;
public:
    GOAPAgent();
    void PerformActions(GOAPEnemy& enemy);
    void PrintState();
};
