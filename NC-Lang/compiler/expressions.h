#pragma once

#include <string>

class IExpression {
private:

public:
    virtual void init(std::string expression) = 0;
};