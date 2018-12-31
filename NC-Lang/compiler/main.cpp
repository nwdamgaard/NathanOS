#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "expressions.h"

int main(int argc, char *argv[]) {
    //first thing to do is get the file(s) we need to compile
    std::vector<std::string> arguments;
    for(int i = 1; i < argc; i++) {
        arguments.push_back(std::string(argv[i]));
    }

    //we're expecting one file name and that's it.
    if(arguments.size() > 1) {
        std::cerr << "Error: Too many arguments.\n";
        return 1;
    }
    std::string filename = arguments[0];

    std::ifstream file(filename);
    if(!file.is_open()) {
        std::cerr << "Error: '" << filename << "' could not be opened\n";
        return 1;
    }

    //step 1: copy source file to memory
    std::string source;
    while(!file.eof()) {
        source.push_back(file.get());
    } 

    //step 2: remove comments
    std::istringstream ss(source);
    source.clear();
    std::string currentLine;
    while(getline(ss, currentLine)) {
        if(currentLine.substr(0, 2) != "//") {
            source.append(currentLine);
        }
    }

    //step 3: split into expressions
    std::vector<std::string> expressionStrings = splitBy(source, ';');

    //step 4: build syntax tree
    std::vector<IExpression*>  expressions;
    for(int i = 0; i < expressionStrings.size(); i++) {
        expressions.push_back(ExpressionFactory::createExpressionFromSource(expressionStrings[i]));
    }

    file.close();
    return 0;
}