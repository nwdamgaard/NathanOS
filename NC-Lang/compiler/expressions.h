#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <regex>

std::string::iterator pushThroughBrackets(std::string::iterator it, std::string* curString);
std::vector<std::string> splitBy(std::string source, const char delimiter);

inline std::string removeWhitespace(std::string str);

//Removes brackets and leading/trailing whitespace
std::string cleanString(std::string str);

class IExpression {
private:

public:
    virtual void init(std::string expression) = 0;
};

class FuncExpression : public IExpression {
private:
    std::string m_source;

    std::string m_name_str;

    std::vector<std::string> m_requirements;
    void splitIntoRequirements();

    //TODO: finish up this function, it currently does not build the tree of expressions
    void parseArguments(const std::string arguments);

    std::vector<IExpression*> m_bodyExpressions;
    void parseBody(const std::string body);

public:
    FuncExpression();
    ~FuncExpression();

    void init(std::string expression);
};

class ExpressionFactory {
public:
    static IExpression* createExpressionFromSource(std::string expressionSource);
};