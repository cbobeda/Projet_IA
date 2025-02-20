#include "BehaviourTreeSetup.hpp"

void BehaviourTreeSetup::setup(BTNode*& root, Blackboard& blackboard, int& currentWaypoint) {
    auto selector = std::make_unique<SelectorNode>();

    
    auto fleeSequence = std::make_unique<SequenceNode>();
    fleeSequence->AddChild(std::make_unique<PlayerDetectedNode>(blackboard, 100.0f));
    fleeSequence->AddChild(std::make_unique<FleeNode>(blackboard, 3.0f));

    
    std::vector<sf::Vector2f> patrolPoints = { {100,100}, {200,100}, {200,200}, {100,200} };
    auto patrolNode = std::make_unique<PatrolNode>(blackboard, patrolPoints, 2.0f, currentWaypoint);

    selector->AddChild(std::move(fleeSequence));
    selector->AddChild(std::move(patrolNode));

    root = selector.release();
}
