#include "PatrolAction.h"

#include "GOAPEnemy.h"


bool PatrolAction::CanExecute(const State& state)
{
    return true;
}
extern Grid grid;

sf::Vector2f normalizeGOAP(const sf::Vector2f& vector)
{
    float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    
    if (length == 0.0f)
        return sf::Vector2f(0.0f, 0.0f);
    return sf::Vector2f(vector.x / length, vector.y / length);
}

bool isClose(sf::Vector2f vector1, sf::Vector2f vector2, float tolerance = 10.f)
{
    return std::hypot(vector1.x - vector2.x, vector1.y - vector2.y) <= tolerance;
}

void PatrolAction::moveTowards(sf::Vector2i targPos,GOAPEnemy& enemy)
{
    if (!isClose(enemy.shape.getPosition(),sf::Vector2f(targPos.x * 40, targPos.y * 40)))
    {
        enemy.shape.move(normalizeGOAP(sf::Vector2f(targPos.x * 40, targPos.y * 40) - enemy.shape.getPosition()));
        //std::cout << normalizeGOAP(enemy.shape.getPosition() - sf::Vector2f(targPos.x * 40, targPos.y * 40)).x <<  normalizeGOAP(enemy.shape.getPosition() - sf::Vector2f(targPos.x * 40, targPos.y * 40)).y << std::endl;
    }
    if (isClose(enemy.shape.getPosition(),sf::Vector2f(targPos.x * 40, targPos.y * 40)))
    {
        //std::cout << "PatrolAction::moveTowards" << std::endl;
        enemy.pathIndex++;
    }
}

void PatrolAction::Execute(State& state,GOAPEnemy& enemy,sf::Vector2i player)
{
    if (enemy.i >= 4) {
        std::cerr << "Erreur : Indice 'i' dépasse la taille de 'position'.\n";
        enemy.i = 0;
        return;
    }
    std::cerr << enemy.pathIndex << std::endl;
    if (enemy.path.size() == 0 || enemy.path.size() == enemy.pathIndex)
    {
        //std::cout << "calculate patrol" << std::endl;
        enemy.path = Pathfinding::findPath(grid, sf::Vector2i(enemy.shape.getPosition().x/40, enemy.shape.getPosition().y / 40), position[enemy.i]);
        std::cout << enemy.pathIndex << std::endl;
    }
    if (!enemy.path.empty() && enemy.pathIndex < enemy.path.size()) {
        moveTowards(enemy.path[enemy.pathIndex], enemy);
    }
    if (isClose(enemy.shape.getPosition(),sf::Vector2f(enemy.path[enemy.path.size()-1].x * 40, enemy.path[enemy.path.size()-1].y * 40)))
    {
        std::cout << "reset\n";
        enemy.pathIndex = 0;
        enemy.i++;
        enemy.agent.state.energy -=10;
        enemy.path.clear();
    }
}