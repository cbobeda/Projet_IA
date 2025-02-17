#include "PatrolAction.h"

#include "GOAPEnemy.h"


bool PatrolAction::CanExecute(const State& state)
{
    return true;
}

void PatrolAction::Execute(State& state,GOAPEnemy& enemy)
{
    std::cout << "Action: patrouille\n";
    if (enemy.i >= 4) {
        std::cerr << "Erreur : Indice 'i' dépasse la taille de 'position'.\n";
        enemy.i = 0;
        return;
    }

    
    if (std::abs(enemy.shape.getPosition().x - position[enemy.i].x) > 0.1f) {
        float dirX = (position[enemy.i].x > enemy.shape.getPosition().x) ? 1.0f : -1.0f;
        enemy.shape.move(dirX * 10, 0);
    }

    
    if (std::abs(enemy.shape.getPosition().y - position[enemy.i].y) > 0.1f) {
        float dirY = (position[enemy.i].y > enemy.shape.getPosition().y) ? 1.0f : -1.0f;
        enemy.shape.move(0, dirY * 10);
    }

    
    if (std::abs(enemy.shape.getPosition().x - position[enemy.i].x) <= 1.1f &&
        std::abs(enemy.shape.getPosition().y - position[enemy.i].y) <= 1.1f) {
        enemy.i++;
        state.energy -= 10;
        if (enemy.i >= 4) {
            enemy.i = 0; 
        }
        }
}