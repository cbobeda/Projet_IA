#pragma once
#include "SelectorNode.hpp"
#include "SequenceNode.h"
#include "PlayerDetectionNode.hpp"
#include "FleeNode.hpp"
#include "PatrolNode.hpp"
#include "Blackboard.hpp"
#include <vector>

class BehaviourTreeSetup {
public:
    static void setup(BTNode*& root, Blackboard& blackboard, int& currentWaypoint);
};
