#pragma once
#include "Action.h"
#include <iostream>
class FleeAction : public Action
{
public:
    bool CanExecute(const State& state) override;
    void Execute(State& state,GOAPEnemy& enemy,sf::Vector2i player) override;
};
