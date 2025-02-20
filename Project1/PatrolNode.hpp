#pragma once
#include "BTNode.h"
#include "Blackboard.hpp"
#include <SFML/System/Vector2.hpp>
#include <vector>

class PatrolNode : public BTNode {
private:
    Blackboard& blackboard;
    std::vector<sf::Vector2f> waypoints;
    float speed;
    int& currentWaypoint;
public:
    PatrolNode(Blackboard& bb, std::vector<sf::Vector2f> points, float patrolSpeed, int& wpIndex);
    NodeState execute() override;
};
