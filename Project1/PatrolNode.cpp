#include "PatrolNode.hpp"
#include <cmath>

PatrolNode::PatrolNode(Blackboard& bb, std::vector<sf::Vector2f> points, float patrolSpeed, int& wpIndex)
    : blackboard(bb), waypoints(points), speed(patrolSpeed), currentWaypoint(wpIndex) {
}

NodeState PatrolNode::execute() {
    if (waypoints.empty()) return NodeState::FAILURE;

    sf::Vector2f enemyPos(blackboard.GetValue("enemy_x"), blackboard.GetValue("enemy_y"));
    sf::Vector2f target = waypoints[currentWaypoint];

    sf::Vector2f direction = target - enemyPos;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length < 5.0f) {  
        currentWaypoint = (currentWaypoint + 1) % waypoints.size();
        return NodeState::SUCCESS;
    }

    direction /= length;  
    enemyPos += direction * speed;

    blackboard.SetValue("enemy_x", static_cast<int>(enemyPos.x));
    blackboard.SetValue("enemy_y", static_cast<int>(enemyPos.y));

    return NodeState::RUNNING;
}
