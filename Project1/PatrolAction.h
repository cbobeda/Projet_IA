#pragma once
#include "Action.h"
#include "SFML/Graphics.hpp"
#include "Pathfinding.h"
#include "Node.h"
#include <iostream>
class PatrolAction : public Action
{
private:
    std::vector<sf::Vector2i> path;
    sf::Vector2i position[4] = {{1,1},{3,1},{3,3},{1,3}};
public:
    bool CanExecute(const State& state) override;
    void Execute(State& state,GOAPEnemy& enemy) override;
};
