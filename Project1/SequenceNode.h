﻿#pragma once
#include <memory>
#include <vector>
#include "BTNode.h"

class SequenceNode : public BTNode {
private:
    std::vector<std::unique_ptr<BTNode>> children;
public:
    void AddChild(std::unique_ptr<BTNode> child);
    NodeState execute() override;
};
