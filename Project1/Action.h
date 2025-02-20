#pragma once
#include "State.h"
#include "Pathfinding.h"
#include "SFML/Graphics.hpp"


class GOAPEnemy;

class Action {
public:
    int cost;
    virtual bool CanExecute(const State& state) = 0;
    virtual void Execute(State& state,GOAPEnemy& enemy,sf::Vector2i player) = 0;
    virtual ~Action() {}
};
