#pragma once
#include "BTNode.h"
#include "Blackboard.hpp"
#include <SFML/System/Vector2.hpp>

class PlayerDetectedNode : public BTNode {
private:
    Blackboard& blackboard;
    float detectionRadius;
public:
    PlayerDetectedNode(Blackboard& bb, float radius);
    NodeState execute() override;
};
