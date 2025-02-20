#include "FollowAction.h"

#include <__msvc_filebuf.hpp>

#include "GOAPEnemy.h"

bool FollowAction::CanExecute(const State& state)
{
    return state.playerInSight;
}
extern Grid grid;
sf::Vector2f normalizeGOAPF(const sf::Vector2f& vector)
{
    float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    
    if (length == 0.0f)
        return sf::Vector2f(0.0f, 0.0f);
    return sf::Vector2f(vector.x / length, vector.y / length);
}

bool isCloseF(sf::Vector2f vector1, sf::Vector2f vector2, float tolerance = 5.f)
{
    return std::hypot(vector1.x - vector2.x, vector1.y - vector2.y) <= tolerance;
}

void moveTowardsF(sf::Vector2i targPos,GOAPEnemy& enemy)
{
    if (!isCloseF(enemy.shape.getPosition(),sf::Vector2f(targPos.x * 40, targPos.y * 40)))
    {
        enemy.shape.move(normalizeGOAPF(sf::Vector2f(targPos.x * 40, targPos.y * 40) - enemy.shape.getPosition()));
        //std::cout << normalizeGOAP(enemy.shape.getPosition() - sf::Vector2f(targPos.x * 40, targPos.y * 40)).x <<  normalizeGOAP(enemy.shape.getPosition() - sf::Vector2f(targPos.x * 40, targPos.y * 40)).y << std::endl;
    }
    if (isCloseF(enemy.shape.getPosition(),sf::Vector2f(targPos.x * 40, targPos.y * 40)))
    {
        //std::cout << "PatrolAction::moveTowards" << std::endl;
        enemy.pathIndex++;
    }
}
void FollowAction::Execute(State& state,GOAPEnemy& enemy,sf::Vector2i player)
{
    if (enemy.i >= 1) {
        std::cerr << "Erreur : Indice 'i' dépasse la taille de 'position'.\n";
        enemy.i = 0;
        return;
    }
    
    if (position[0] != player)
    {
        position[0] = player;
        enemy.path.clear();
    }
    
    std::cerr << enemy.pathIndex << std::endl;
    if (enemy.path.size() == 0 || enemy.path.size() == enemy.pathIndex)
    {
        //std::cout << "calculate patrol" << std::endl;
        enemy.path = Pathfinding::findPath(grid, sf::Vector2i(enemy.shape.getPosition().x/40, enemy.shape.getPosition().y / 40), position[enemy.i]);
        std::cout << enemy.pathIndex << std::endl;
    }
    if (!enemy.path.empty() && enemy.pathIndex < enemy.path.size() && !isCloseF(enemy.shape.getPosition(),sf::Vector2f(enemy.path[enemy.path.size()-1].x * 40, enemy.path[enemy.path.size()-1].y * 40))) {
        moveTowardsF(enemy.path[enemy.pathIndex], enemy);
        enemy.agent.state.energy -=1;
    }
    if (isCloseF(enemy.shape.getPosition(),sf::Vector2f(enemy.path[enemy.path.size()-1].x * 40, enemy.path[enemy.path.size()-1].y * 40)))
    {
        std::cout << "reset\n";
        enemy.i++;
        enemy.agent.state.playerInRange = true;
        enemy.path.clear();
    }
}