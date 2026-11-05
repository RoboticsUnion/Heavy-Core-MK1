#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <list>

class TerminalInterpreter
{
private:
    void output(std::string output);
    //void test(std::list<std::string> arguments); only test sketch
public:
    void interpret(std::string input);
};

extern TerminalInterpreter terminal_interpret;
