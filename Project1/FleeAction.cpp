#include "FleeAction.h"


bool FleeAction::CanExecute(const State& state)
{
    return state.lowHealth;
}

void FleeAction::Execute(State& state,GOAPEnemy& enemy)
{
    std::cout << "Action: fui le joueur\n";
}

