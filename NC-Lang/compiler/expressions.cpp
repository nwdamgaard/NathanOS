#include "expressions.h"

std::string::iterator pushThroughBrackets(std::string::iterator it, std::string* curString) {
    while(*it != ')') {
        curString->push_back(*it);
        if(*it == '(') {
            it++;
            it = pushThroughBrackets(it, curString);
            curString->push_back(*it);
        }
        it++;
    }
    return it;
}

std::vector<std::string> splitBy(std::string source, const char delimiter) {
    //loop through characters until we find delimiter but if a '(' comes first we skip to the matching ')' before continuing to look for the ';'
    std::vector<std::string> expressions;
    std::string curString = "";
    for(std::string::iterator it = source.begin(); it != source.end(); it++) {
        if(*it == '(') {
            curString.push_back(*it);
            it++;
            it = pushThroughBrackets(it, &curString);
        }
        if(*it == delimiter) {
            curString.push_back(*it);
            expressions.push_back(curString);
            curString.clear();
            continue;
        }
        curString.push_back(*it);
    }

    if(curString != "" && curString[0] != (char)-1) {
        expressions.push_back(curString);
    }

    return expressions;
}

std::string removeWhitespace(std::string str) {
    std::string returnVal = std::regex_replace(str, std::regex("^ +| +$|( ) +"), "$1");
    return returnVal;
}

std::string cleanString(std::string str) {
    //remove the brackets and leading/trailing whitespace
    std::string returnVal = removeWhitespace(str);
    returnVal = returnVal.substr(1, returnVal.size());
    returnVal = returnVal.substr(0, returnVal.size() - 1);
    return returnVal;
}

FuncExpression::FuncExpression() {

}

FuncExpression::~FuncExpression() {

}

void FuncExpression::init(std::string source) {
    m_source = source.substr(5, source.size()); //remove the 'func'
    m_source = m_source.substr(0, m_source.size() - 1); //remove the ';'

    splitIntoRequirements();
    std::string name_str = m_requirements[0];
    std::string arguments_str = m_requirements[1];
    std::string body_str = m_requirements[2];

    parseArguments(arguments_str);
    parseBody(body_str);
}

void FuncExpression::splitIntoRequirements() {
    //std::cout << m_source << std::endl << std::endl;
    m_requirements = splitBy(m_source, ' ');

    //validate requirements
    if(m_requirements.size() != 3) {
        std::cerr << "Error: Wrong number of requirements in function definition:" << std::endl;
        std::cerr << "  Function definition needs 3 requirements, " << m_requirements.size() << " provided." << std::endl;
    }
}

void FuncExpression::parseArguments(const std::string arguments) {
    std::string argumentsToSplit = cleanString(arguments);

    std::vector<std::string> argumentStrings = splitBy(argumentsToSplit, ';');

    for(int i = 0; i < argumentStrings.size(); i++) {
        //std::cout << argumentStrings[i] << std::endl;
    }
}

void FuncExpression::parseBody(const std::string body) {
    std::string preparedBody = cleanString(body);

    std::vector<std::string> bodyStrings = splitBy(preparedBody, ';');

    for(int i = 0; i < bodyStrings.size(); i++) {
        bodyStrings[i] = removeWhitespace(bodyStrings[i]);
        m_bodyExpressions.push_back(ExpressionFactory::createExpressionFromSource(bodyStrings[i]));
    }
}

IExpression* ExpressionFactory::createExpressionFromSource(std::string source) {
    IExpression* expression = nullptr;
    if(source.substr(0, 4) == "func") {
        expression = new FuncExpression();
    }

    if(expression == nullptr) {
        std::cerr << "Error: Invalid Expression" << std::endl;
    } else {
        expression->init(source);
    }
    return expression;
}