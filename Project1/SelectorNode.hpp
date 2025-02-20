#pragma once
#include "BTNode.h"
#include <memory>
#include <vector>

class SelectorNode : public BTNode {
private:
    std::vector<std::unique_ptr<BTNode>> children;


public :
    void AddChild(std::unique_ptr<BTNode> child);

    NodeState execute() override;
};

