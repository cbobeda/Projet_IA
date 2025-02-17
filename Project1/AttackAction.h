#pragma once
#include "Action.h"
#include <iostream>
class AttackAction : public Action
{
public:
    bool CanExecute(const State& state) override;
    void Execute(State& state,GOAPEnemy& enemy) override;
};
