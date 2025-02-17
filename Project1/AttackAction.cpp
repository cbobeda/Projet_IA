#include "AttackAction.h"
bool AttackAction::CanExecute(const State& state)
{
    return state.playerInRange;
}

void AttackAction::Execute(State& state,GOAPEnemy& enemy)
{
    std::cout << "Action: attaque le joueur\n";
}

