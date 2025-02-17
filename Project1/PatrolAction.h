#pragma once
#include "Action.h"
#include "SFML/Graphics.hpp"
#include <iostream>
class PatrolAction : public Action
{
private:
    
    sf::Vector2f position[4] = {{100,100},{300,100},{300,300},{100,300}};
public:
    bool CanExecute(const State& state) override;
    void Execute(State& state,GOAPEnemy& enemy) override;
};
