#include "GOAPPlanner.h"


std::vector<std::unique_ptr<Action>> GOAPPlanner::Plan(const State& initialState)
{
    int temp = 10000;
    int index;

    std::vector<std::unique_ptr<Action>> plan;
    std::vector <std::unique_ptr<Action>> costs;

    std::unique_ptr<PatrolAction> patrol = std::make_unique<PatrolAction>();
    std::unique_ptr<FollowAction> follow = std::make_unique<FollowAction>();
    std::unique_ptr<AttackAction> attack = std::make_unique<AttackAction>();
    std::unique_ptr<FleeAction> flee = std::make_unique<FleeAction>();
    
    patrol->cost = initialState.playerInSight * 100 - initialState.energy;
    costs.push_back(std::move(patrol));
    follow->cost = initialState.health - initialState.energy * !initialState.lowHealth;
    costs.push_back(std::move(follow));
    attack->cost = initialState.health - initialState.energy * !initialState.playerInRange;
    costs.push_back(std::move(attack));
    flee->cost = !initialState.lowHealth * 100;
    costs.push_back(std::move(flee));

    for (int i = 0; i < 4;i++)
    {
        if (costs[i]->cost < temp)
        {
            temp = costs[i]->cost;
            index = i;
        }
    }

    plan.push_back(std::move(costs[index]));

    return plan;

}
