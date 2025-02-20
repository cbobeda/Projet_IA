#include "FleeNode.hpp"
#include <cmath>

FleeNode::FleeNode(Blackboard& bb, float fleeSpeed)
    : blackboard(bb), speed(fleeSpeed) {
}

NodeState FleeNode::execute() {
    sf::Vector2f enemyPos(blackboard.GetValue("enemy_x"), blackboard.GetValue("enemy_y"));
    sf::Vector2f playerPos(blackboard.GetValue("player_x"), blackboard.GetValue("player_y"));

    sf::Vector2f direction = enemyPos - playerPos;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length == 0) return NodeState::FAILURE;

    direction /= length;  
    enemyPos += direction * speed;  

    blackboard.SetValue("enemy_x", static_cast<int>(enemyPos.x));
    blackboard.SetValue("enemy_y", static_cast<int>(enemyPos.y));

    return NodeState::RUNNING;
}
