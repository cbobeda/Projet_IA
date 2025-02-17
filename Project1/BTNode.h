#pragma once
#include "NodeState.h"

class BTNode {
public:
    virtual ~BTNode() = default;
    virtual NodeState execute() = 0;
};