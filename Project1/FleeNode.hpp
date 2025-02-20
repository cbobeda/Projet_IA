#pragma once
#include "BTNode.h"
#include "Blackboard.hpp"
#include <SFML/System/Vector2.hpp>

class FleeNode : public BTNode {
private:
    Blackboard& blackboard;
    float speed;
public:
    FleeNode(Blackboard& bb, float fleeSpeed);
    NodeState execute() override;
};
