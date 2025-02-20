#pragma once
#include "Action.h"
#include <iostream>
class FollowAction : public Action
{
private:
    sf::Vector2i position[1] = {{1,1}};
public:
    bool CanExecute(const State& state) override;
    void Execute(State& state,GOAPEnemy& enemy,sf::Vector2i player) override;
};
