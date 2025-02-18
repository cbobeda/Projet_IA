#pragma once
#include "Action.h"
#include "SFML/Graphics.hpp"
#include "Pathfinding.h"
#include <iostream>
class PatrolAction : public Action
{
private:
    
    sf::Vector2i position[4] = {{5,5},{10,10},{5,3},{10,3}};
public:
    void moveTowards(sf::Vector2i targPos,GOAPEnemy& enemy);
    bool CanExecute(const State& state) override;
    void Execute(State& state,GOAPEnemy& enemy) override;
};
