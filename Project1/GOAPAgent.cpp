#include "GOAPAgent.h"

GOAPAgent::GOAPAgent()
{
    state.health = 100;
    state.energy = 100;
    state.lowHealth = false;
    state.playerInSight = false;
}

void GOAPAgent::PerformActions(GOAPEnemy& enemy,sf::Vector2i player)
{
    std::vector<std::unique_ptr<Action>> plan = planner.Plan(state);

    for (auto& action : plan) {
        if (action->CanExecute(state)) {
            action->Execute(state,enemy,player);  // Exécute l'action
        }
        else {
            std::cout << "Action impossible : " << typeid(*action).name() << "\n";
        }
    }
}

void GOAPAgent::PrintState()
{
    std::cout << "Health: " << state.health << "\n";
    std::cout << "Low ?: " << (state.lowHealth ? "Oui" : "Non") << "\n";
    std::cout << "Energie: " << state.energy << "\n";
    std::cout << "Joueur ?: " << (state.playerInSight ? "Oui" : "Non") << "\n";
}
