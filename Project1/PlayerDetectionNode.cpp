#include "PlayerDetectionNode.hpp"
#include <cmath>

PlayerDetectedNode::PlayerDetectedNode(Blackboard& bb, float radius)
    : blackboard(bb), detectionRadius(radius) {
}

NodeState PlayerDetectedNode::execute() {
    sf::Vector2f enemyPos(blackboard.GetValue("enemy_x"), blackboard.GetValue("enemy_y"));
    sf::Vector2f playerPos(blackboard.GetValue("player_x"), blackboard.GetValue("player_y"));

    float dx = playerPos.x - enemyPos.x;
    float dy = playerPos.y - enemyPos.y;
    float distance = std::sqrt(dx * dx + dy * dy);

    return (distance <= detectionRadius) ? NodeState::SUCCESS : NodeState::FAILURE;
}
