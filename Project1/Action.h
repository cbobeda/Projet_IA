#pragma once
#include "State.h"


class GOAPEnemy;

class Action {
public:
    int cost;
    virtual bool CanExecute(const State& state) = 0;
    virtual void Execute(State& state,GOAPEnemy& enemy) = 0;
    virtual ~Action() {}
};
