#include "AttackAction.h"
#include "GOAPEnemy.h"

bool AttackAction::CanExecute(const State& state)
{
    return state.playerInRange;
}

void AttackAction::Execute(State& state,GOAPEnemy& enemy,sf::Vector2i player)
{
    enemy.shape.setFillColor(sf::Color::Green);
}