#include "FollowAction.h"

bool FollowAction::CanExecute(const State& state)
{
    return state.playerInSight;
}

void FollowAction::Execute(State& state,GOAPEnemy& enemy)
{
    std::cout << "Action: suis le joueur\n";
}