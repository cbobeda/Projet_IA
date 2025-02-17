#pragma once
#include <memory>
#include <vector>
#include "State.h"
#include "PatrolAction.h"
#include "FollowAction.h"
#include "AttackAction.h"
#include "FleeAction.h"
class GOAPPlanner
{
public:
    std::vector<std::unique_ptr<Action>> Plan(const State& initialState);
};
